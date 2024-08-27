# By Nikku4211
# Based on UGE2Source.py by Valen (Coffee Bat)
import argparse

# TODO: Add sgb warning text

parser = argparse.ArgumentParser()
parser.add_argument("uge", help=".UGE File input.")
parser.add_argument("outfile", help="File output.")
#parser.add_argument("-b", help="Bank value")
#parser.add_argument("-op", help="Optimize patterns", action='store_true')
#parser.add_argument("-oi", help="Optimize instruments/waves", action='store_true')
parser.add_argument("-f", help="Display Info")
parser.add_argument("-sfx", help="Sound effect channel (if any)", choices=range(6), type=int)

args = parser.parse_args()

noteConsts = ["C_3","Cs3","D_3","Ds3","E_3","F_3","Fs3","G_3","Gs3","A_3","As3","B_3","C_4","Cs4","D_4","Ds4","E_4","F_4","Fs4","G_4","Gs4","A_4","As4","B_4","C_5","Cs5","D_5","Ds5","E_5","F_5","Fs5","G_5","Gs5","A_5","As5","B_5","C_6","Cs6","D_6","Ds6","E_6","F_6","Fs6","G_6","Gs6","A_6","As6","B_6","C_7","Cs7","D_7","Ds7","E_7","F_7","Fs7","G_7","Gs7","A_7","As7","B_7","C_8","Cs8","D_8","Ds8","E_8","F_8","Fs8","G_8","Gs8","A_8","As8","B_8"]

hexLUT = "0123456789ABCDEF"

class DutyInstrument:
    index = 0
    name = ""
    length = 0
    duty_cycle = 0
    initial_volume = 0
    volume_sweep_change = 0
    frequency_sweep_time = 0
    frequency_sweep_shift = 0
    subpattern = []

class WaveInstrument:
    index = 0
    name = ""
    length = 0
    volume = 0
    wave_index = 0
    subpattern = []

class NoiseInstrument:
  index = 0
  name = ""
  length = 0
  initial_volume = 0
  volume_sweep_change = 0
  shift_clock_mask = 0
  dividing_ratio = 0
  bit_count = 0
  noise_macro = []
  subpattern = []

class Song:
    def __init__(self,name,artist,comment,duty_instruments,wave_instruments,noise_instruments,waves,ticks_per_row,patterns,orders):
        self.name = name
        self.artist = artist
        self.comment = comment
        self.duty_instruments = duty_instruments
        self.wave_instruments = wave_instruments
        self.noise_instruments = noise_instruments
        self.waves = waves
        self.ticks_per_row = ticks_per_row
        self.patterns = patterns
        self.orders = orders

def loadUGESong(data):
    offset = 0
    uge_version = int.from_bytes(data[offset:offset + 4], "little")
    offset += 4

    song_name = (data[offset + 1:offset + 1 + data[offset]]).decode("utf-8").replace(" ","_")
    offset += 256

    song_artist = (data[offset + 1:offset + 1 + data[offset]]).decode("utf-8")
    offset += 256

    song_comment = (data[offset + 1:offset + 1 + data[offset]]).decode("utf-8")
    offset += 256

    instrument_count = 15 if uge_version < 3 else 45

    duty_instruments = []
    wave_instruments = []
    noise_instruments = []

    # Collect instruments
    for n in range(0, instrument_count):
        type_ = int.from_bytes(data[offset:offset + 4], "little")
        offset += 4

        name = (data[offset + 1:offset + 1 + data[offset]]).decode("utf-8")
        offset += 256

        length = int.from_bytes(data[offset:offset + 4], "little")
        offset += 4

        length_enabled = data[offset]
        offset += 1

        initial_volume = data[offset]
        if initial_volume > 15:
            initial_volume = 15 # ??? bug in the song files?
        offset += 1

        volume_direction = int.from_bytes(data[offset:offset + 4], "little")
        offset += 4

        volume_sweep_amount = data[offset]
        offset += 1

        # I think this bit of code only matters for GB Studio
        #if volume_sweep_amount != 0:
            #volume_sweep_amount = 8 - volume_sweep_amount
        if volume_direction != 0:
            volume_sweep_amount = -volume_sweep_amount

        freq_sweep_time = int.from_bytes(data[offset:offset + 4], "little")
        offset += 4

        freq_sweep_direction = int.from_bytes(data[offset:offset + 4], "little")
        offset += 4

        freq_sweep_shift = int.from_bytes(data[offset:offset + 4], "little")
        offset += 4

        # I think this bit is also relevant to GB Studio only
        if freq_sweep_direction > 0:
            freq_sweep_shift = -freq_sweep_shift

        duty = data[offset]
        offset += 1

        wave_output_level = int.from_bytes(data[offset:offset + 4], "little")
        offset += 4

        wave_waveform_index = int.from_bytes(data[offset:offset + 4], "little")
        offset += 4
        
        if uge_version < 6:
            offset += 4

        noise_counter_step = int.from_bytes(data[offset:offset + 4], "little")
        offset += 4

        noise_macro = []
        subpattern = []
        if uge_version >= 4 and uge_version < 6:
            offset += 4
            for x in range(0, 6):
                uint8ref = data[offset]
                # GB Studio only
                #int8ref = uint8ref - 0x100 if uint8ref > 0x7f else uint8ref
                noise_macro.append(uint8ref)
                offset += 1
        elif uge_version >= 6:
            subpattern_enabled = data[offset]
            offset += 1
            
            for m in range(0, 64):
                note = int.from_bytes(data[offset:offset + 4], "little")
                offset += 8
                jumpparam = int.from_bytes(data[offset:offset + 4], "little")
                offset += 4
                effectcode = int.from_bytes(data[offset:offset + 4], "little")
                offset += 4

                effectparam = data[offset]
                offset += 1

                # Possible SGB Overflow (C3 is 0 in SGB)
                if note == 0 and (effectcode == 2 or effectcode == 1 or effectcode == 3):
                    effectcode = 0
                    effectparam = 0

                #print(noteConsts[note] if note < 90 else "---", instrument, hex(effectcode)[2:], hex(effectparam)[2:])
                subpattern.append([note, jumpparam, effectcode, effectparam])

        # Duty
        if type_ == 0:
            # GB Studio only? Idk
            length = 64 - length

            instr = DutyInstrument()

            if length_enabled:
                instr.length = length
            else:
                instr.length = None

            instr.name = name
            instr.duty_cycle = duty
            instr.initial_volume = initial_volume
            instr.volume_sweep_change = volume_sweep_amount
            
            instr.frequency_sweep_time = freq_sweep_time
            instr.frequency_sweep_shift = freq_sweep_shift

            duty_instruments.append(instr)

        # Wave
        elif type_ == 1:
            # GB Studio only? Idk
            length = 256 - length

            instr = WaveInstrument()

            if length_enabled:
                instr.length = length
            else:
                instr.length = None
            
            instr.name = name
            instr.volume = wave_output_level
            instr.wave_index = wave_waveform_index

            wave_instruments.append(instr)

        # Noise
        elif type_ == 2:
            # GB Studio only? Idk
            length = 64 - length

            instr = NoiseInstrument()

            if length_enabled:
                instr.length = length
            else:
                instr.length = None

            instr.name = name
            instr.initial_volume = initial_volume
            instr.volume_sweep_change = volume_sweep_amount
            
            instr.bit_count = 7 if noise_counter_step else 15
            if uge_version >= 4 and uge_version < 6:
                instr.noise_macro = noise_macro
            elif uge_version < 4:
                instr.noise_macro = [0, 0, 0, 0, 0, 0]

            noise_instruments.append(instr)
        else:
            print("Invalid Instrument type", type_)

    # Collect waves
    waves = []
    for n in range(0, 16):
        waves.append(list(data[offset:offset + 32]))
        offset += 32

        # older versions have an off-by-one error
        if uge_version < 3:
            offset += 1

    song_ticks_per_row = int.from_bytes(data[offset:offset + 4], "little")
    offset += 4
    
    if uge_version >= 6:
        timer_tempo_enabled = data[offset]
        offset += 1
        timer_tempo_divider = int.from_bytes(data[offset:offset + 4], "little")
        offset += 4

    pattern_count = int.from_bytes(data[offset:offset + 4], "little")

    if (offset + pattern_count * (17 if uge_version >= 6 else 13) * 64 > len(data)):
        print("Song has too many patterns (%d)" % pattern_count)
    offset += 4

    patterns = [None] * 128

    for n in range(0, pattern_count):
        patternId = 0
        pattern = []
        if uge_version >= 5:
            patternId = int.from_bytes(data[offset:offset + 4], "little")
            offset += 4
        else:
            patternId = n
        for m in range(0, 64):
            note = int.from_bytes(data[offset:offset + 4], "little", signed=True)
            offset += 4
            instrument = int.from_bytes(data[offset:offset + 4], "little", signed=True)
            offset += 4
            if uge_version >= 6:
                offset += 4
            effectcode = int.from_bytes(data[offset:offset + 4], "little", signed=True)
            offset += 4

            effectparam = data[offset]
            offset += 1

            # Possible SGB Overflow (C3 is 0 in SGB)
            if note == 0 and (effectcode == 2 or effectcode == 1 or effectcode == 3):
                effectcode = 0
                effectparam = 0

            #print(noteConsts[note] if note < 90 else "---", instrument, hex(effectcode)[2:], hex(effectparam)[2:])
            pattern.append([note, instrument, effectcode, effectparam])


        # I don't know what the fuck the og code was doing so lol
        #patterns.append(pattern)
        if (uge_version == 5 and patterns[patternId] != None):
            patterns[n] = pattern
        else:
            patterns[patternId] = pattern

    orders = []
    for n in range(0, 4):
        ch = []
        order_count = int.from_bytes(data[offset:offset + 4], "little") # The amount of pattern orders stored in the file has an off-by-one.
        offset += 4
        for m in range(0, order_count-1):
            ch.append(int.from_bytes(data[offset:offset + 4], "little"))
            offset += 4
        offset += 4 # Blank byte after channel order end?
        orders.append(ch)

    data_used = [0,0,0,0] # Duty ins, Wave Ins, Noise ins, Waves
    wav_ins_used = [False] * 16

    for n in range(0, order_count - 1):
        # Analyze duty patterns and get highest used instrument
        patA = patterns[orders[0][n]]
        patB = patterns[orders[1][n]]
        patC = patterns[orders[2][n]]
        patD = patterns[orders[3][n]]

        for m in range(0, 64):
            if patA[m][1] > data_used[0]:
                data_used[0] = patA[m][1]
            if patB[m][1] > data_used[0]:
                data_used[0] = patB[m][1]

            if patC[m][1] > data_used[1]:
                data_used[1] = patC[m][1]
            wav_ins_used[patC[m][1]] = True
            
            if patD[m][1] > data_used[2]:
                data_used[2] = patD[m][1]

    for n in range(0,15):
        if wav_ins_used[n] == True:
            if wave_instruments[n].wave_index > data_used[3]:
                data_used[3] = wave_instruments[n].wave_index

    # if args.oi:
        # duty_instruments = duty_instruments[0:data_used[0]]
        # wave_instruments = wave_instruments[0:data_used[1]]
        # noise_instruments = noise_instruments[0:data_used[2]]
        # waves = waves[0:data_used[3]+1]

    # Optimize patterns if needed
    # if args.op:   
        # for n in range(len(patterns)):
            # if patterns[n] == None:
                # continue
            # for m in range(0, len(patterns[n])):
                # if patterns[n][m][2] == 0xB or patterns[n][m][2] == 0xD:
                    # if patterns[n][m][3] != 0:
                        # patterns[n] = patterns[n][0:m+1]
                        # break
                # elif patterns[n][m][2] == 0xF and patterns[n][m][3] == 0x0:
                    # patterns[n] = patterns[n][0:m+1]
                    # break

    return Song(song_name,song_artist,song_comment,duty_instruments,wave_instruments,noise_instruments,waves,song_ticks_per_row,patterns,orders)
    
f = open(args.uge, "rb")
song = loadUGESong(f.read())
c_file = open(args.outfile, "w")
h_file = open((args.outfile.split(".")[0]+".h"),"wt")
c_file.write("""#include "../source/advikku_global.h"
#include <stdint.h>
#include <tonc.h>

#include "blank_raw.h"

/*
    Song name:  %s
    Artist:     %s

    Converted using Nikku4211's ugetoadvik.py based on code by Valen Coffee Bat's uge2source.py
*/
""" % (song.name, song.artist))
h_file.write("""#pragma once
#include "../source/advikku_global.h"
#include <stdint.h>
#include <tonc.h>

#include "blank_raw.h"

/*
    Song name:  %s
    Artist:     %s

    Converted using Nikku4211's ugetoadvik.py based on code by Valen Coffee Bat's uge2source.py
*/
""" % (song.name, song.artist))

c_file.write("""#define END 0xff
#define HOLD 0xfe
""")

c_file.write("""
//speed
//version
//channels
//song length in orders per channel
//song order loopstart
//commands linger flag
//use subpatterns flag

const uint8_t %sSongHeader[] = {
    0x%02x,
    0x01,
    0x04,
    0x%02x,
    0x00,
    0x00,
    0x00
};
""" % (song.name, song.ticks_per_row, len(song.orders[0])))

h_file.write("\nextern const uint8_t %sSongHeader[];" % song.name)

# Compile all USED patterns
u_patterns = []
for n in range(4):
    for m in range(len(song.orders[n])):
        p = song.orders[n][m]
        if p not in u_patterns:
            u_patterns.append(p)

# Compile patterns
if args.sfx == None:
    for n in u_patterns:
        cur_p = song.patterns[n]
        c_file.write("\nconst uint8_t " + song.name + "SongOrder" + str(n) + "[] = {\n")
        h_file.write("\nextern const uint8_t %sSongOrder%d[];" % (song.name, n))
        for m in range(0, len(cur_p)):
            note = str(cur_p[m][0]) if cur_p[m][0] < 90 else "HOLD"
            instrument = str(cur_p[m][1])
            effectcode = cur_p[m][2]
            effectparam = cur_p[m][3]
            
            match effectcode:
                case 6 | 0x0A:
                    effect = "0x0" + hexLUT[0] + ", 0x" + hexLUT[0] + hexLUT[0]
                case _:
                    effect = "0x0" + hexLUT[effectcode] + ", 0x" + hexLUT[effectparam >> 4] + hexLUT[effectparam & 0xF]

            c_file.write("" + note + "," + instrument + "," + effect + ",\n")
        c_file.write("END\n};")
else:
    cur_p = song.patterns[0]
    c_file.write("\nconst uint8_t " + song.name + "SongOrder0[] = {\n")
    h_file.write("\nextern const uint8_t %sSongOrder0[];" % song.name)
    for m in range(0, len(cur_p)):
        note = str(cur_p[m][0]) if cur_p[m][0] < 90 else "HOLD"
        instrument = str(cur_p[m][1])
        effectcode = cur_p[m][2]
        effectparam = cur_p[m][3]
        
        match effectcode:
            case 6 | 0x0A:
                effect = "0x0" + hexLUT[0] + ", 0x" + hexLUT[0] + hexLUT[0]
            case _:
                effect = "0x0" + hexLUT[effectcode] + ", 0x" + hexLUT[effectparam >> 4] + hexLUT[effectparam & 0xF]

        c_file.write("" + note + "," + instrument + "," + effect + ",\n")
    c_file.write("END\n};")
    
c_file.write("\n")

if args.sfx == None:
    c_file.write("\nconst uint8_t* const " + song.name + "Song[] = {")
    h_file.write("\nextern const uint8_t* const %sSong[];" % song.name)
    # Compile orders
    for m in range(0, len(song.orders[0])):
        for n in range(0, 4):
            c_file.write("\n" + song.name + "SongOrder" + str(song.orders[n][m]) + ",")
    c_file.write("\n};")

# Compile waves
if len(song.waves):
    for n in range(0, len(song.waves)):
        c_file.write("\nconst uint16_t " + song.name + "Waveform" + str(n) + "[] = {")
        h_file.write("\nextern const uint16_t %sWaveform%d[];" % (song.name, n))
        for m in range(0, 8):
            b = (song.waves[n][m * 4] << 12) | (song.waves[n][(m * 4) + 1] << 8) | (song.waves[n][(m * 4) + 2] << 4) | song.waves[n][(m * 4) + 3]
            c_file.write("\n    0x%04x," % b)
        c_file.write("\n};\n")

# Compile duty instruments
if len(song.duty_instruments):
    c_file.write("\n\nconst uint16_t " + song.name + "SquareInstruments[] = {")
    h_file.write("\nextern const uint16_t %sSquareInstruments[];" % song.name)

    for n in range(0, len(song.duty_instruments)):
        inst = song.duty_instruments[n]

        # For some reason sweep shift is off (Inverted?)
        #rNR10 = (inst.frequency_sweep_time << 4) | (0x00 if inst.frequency_sweep_shift < 0 else 0x08) | abs(inst.frequency_sweep_shift);
        #rNR11 = (inst.duty_cycle << 6) | (64 - inst.length if inst.length != None else 63)
        #rNR12 = (inst.initial_volume << 12) | (0x0800 if inst.volume_sweep_change > 0 else 0)
        
        #if inst.volume_sweep_change != 0:
            #rNR12 |= abs(inst.volume_sweep_change)

        c_file.write("\n SSQR_LEN(%d) | SSQR_TIME(%d) | SSQR_IVOL(%d) | SSQR_DUTY(%d)" % (64 - inst.length if inst.length != None else 0, abs(inst.volume_sweep_change), inst.initial_volume, inst.duty_cycle))
        
        match inst.volume_sweep_change:
            case inst.volume_sweep_change if inst.volume_sweep_change > 0:
                c_file.write(" | SSQR_DEC,")
            case _:
                c_file.write(" | SSQR_INC,")
                
    c_file.write("\n};")

# Compile wave instruments
if len(song.wave_instruments):
    c_file.write("\nconst uint16_t " + song.name + "WaveInstruments[] = {")
    h_file.write("\nextern const uint16_t %sWaveInstruments[];" % song.name)
    for n in range(0, len(song.wave_instruments)):
        inst = song.wave_instruments[n]
        #rNR31 = (inst.length if inst.length != None else 63) & 0xff;
        #rNR32 = inst.volume << 13
        #wave_nr = inst.wave_index
        #rNR34 = (0x4000 if inst.length != None else 0)
        c_file.write("\n SWAV_LEN(%d)" % (256 - inst.length if inst.length != None else 0))
        match inst.volume:
            case 0:
                c_file.write(" | SWAV_VOL0,")
            case 1:
                c_file.write(" | SWAV_VOL100,")
            case 2:
                c_file.write(" | SWAV_VOL50,")
            case 3:
                c_file.write(" | SWAV_VOL25,")
        match inst.length:
            case None:
                c_file.write(" SWAV_LEN_OFF,")
            case _:
                c_file.write(" SWAV_LEN_ON,")
    c_file.write("\n};")

# Compile used waveforms
if len(song.wave_instruments):
    c_file.write("\nconst uint16_t * const " + song.name + "Waveforms[] = {")
    h_file.write("\nextern const uint16_t * const %sWaveforms[];" % song.name)
    for n in range(0, len(song.wave_instruments)):
        inst = song.wave_instruments[n]
        wave_nr = inst.wave_index
        c_file.write("\n" + song.name + "Waveform" + str(wave_nr) + ",")
    c_file.write("\n};")    
        

# Compile noise instruments
if len(song.noise_instruments):
    c_file.write("\nconst uint16_t " + song.name + "NoiseInstruments[] = {")
    h_file.write("\nextern const uint16_t %sNoiseInstruments[];" % song.name)
    for n in range(0, len(song.noise_instruments)):
        inst = song.noise_instruments[n]
        
        #param0 = (inst.initial_volume << 12) | (0x0800 if inst.volume_sweep_change > 0 else 0)

        #if inst.volume_sweep_change != 0:
            #param0 |= abs(inst.volume_sweep_change)
        #print(inst.volume_sweep_change)
        #param1 = (64 - inst.length if inst.length != None else 63) & 0x3f
        
        #if inst.bit_count == 7:
            #param1 |= 0x0040

        c_file.write("\n SSQR_LEN(%d) | SSQR_TIME(%d) | SSQR_IVOL(%d)" % (64 - inst.length if inst.length != None else 0, abs(inst.volume_sweep_change), inst.initial_volume))
        
        match inst.volume_sweep_change:
            case inst.volume_sweep_change if inst.volume_sweep_change > 0:
                c_file.write(" | SSQR_DEC")
            case _:
                c_file.write(" | SSQR_INC")
        
        match inst.bit_count:
            case 7:
                c_file.write(" | SNOI_SHORT_PACK,")
            case _:
                c_file.write(" | SNOI_LONG_PACK,")
        
    c_file.write("\n};\n")
 
c_file.write("""const uint8_t * const %sDMAInstruments[] = {
    blank_raw
};

const uint16_t %sDMADurations[] = {
    0
};
""" % (song.name, song.name))

h_file.write("""\nextern const uint8_t * const %sDMAInstruments[];

extern const uint16_t %sDMADurations[];
""" % (song.name, song.name))

if args.sfx == None:
    c_file.write("""const advikSongStruct %sSongStruct = {
    %sSong,
    %sSongHeader,
    %sSquareInstruments,
    %sWaveInstruments,
    %sWaveforms,
    %sNoiseInstruments,
    %sDMAInstruments,
    %sDMADurations
    };\n""" % (song.name, song.name, song.name, song.name, song.name, song.name, song.name, song.name, song.name))

    h_file.write("""extern const advikSongStruct %sSongStruct;\n""" % (song.name))
else:
    c_file.write("""const advikSFXStruct %sSFXStruct = {
    %sSongOrder0,
    %sSongHeader,
    %sSquareInstruments,
    %sWaveInstruments,
    %sWaveforms,
    %sNoiseInstruments,
    %sDMAInstruments,
    %sDMADurations
    };\n""" % (song.name, song.name, song.name, song.name, song.name, song.name, song.name, song.name, song.name))

    h_file.write("""extern const advikSFXStruct %sSFXStruct;\n""" % (song.name))

c_file.close()

h_file.close()

print(args.outfile,"compiled succesfully.")