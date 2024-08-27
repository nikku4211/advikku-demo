import sys
from chipchune.furnace.module import FurnaceModule, FurnacePattern
from chipchune.furnace.enums import ChipType, Note, InstrumentType, MacroCode, MacroType
import chipchune.utils.conversion as convert
import chipchune.furnace.data_types as datype
from typing import cast, List

note_to_absolute = {
    Note.__: 0xFE,
    Note.OFF: 0xFE,
    Note.OFF_REL: 0xFE,
    Note.REL: 0xFE,
    Note.C_: 0,
    Note.Cs: 1,
    Note.D_: 2,
    Note.Ds: 3,
    Note.E_: 4,
    Note.F_: 5,
    Note.Fs: 6,
    Note.G_: 7,
    Note.Gs: 8,
    Note.A_: 9,
    Note.As: 10,
    Note.B_: 11,
}

def fur2adv(module: FurnaceModule, sfx=False, sfx_chan=0) -> List[str]:
    daconly = False
    if not (
        (len(module.chips.list) > 1 and
        module.chips.list[0].type == ChipType.GB and 
        module.chips.list[1].type == ChipType.GBA) or
        module.chips.list[0].type == ChipType.GB or
        module.chips.list[0].type == ChipType.GBA
    ):
        raise Exception("Not a (Furnace) GB and/or GBA DAC module")
    elif (
        module.chips.list[0].type == ChipType.GBA
    ):
        daconly = True
        
    title = module.meta.name.replace(" ","_")
    
    lines: List[str] = []
    hlines: List[str] = []
    
    lines += [
    "#include <stdint.h>",
    "#include <tonc.h>",
    "//converted by Nikku4211's furtoadvik.py, reliant on zumi.dxy's chipchune.py",
    "#include \"../source/advikku_global.h\"",
    "#include \"blank_raw.h\""
    ]
    
    hlines += [
    "#pragma once",
    "#include <stdint.h>",
    "#include <tonc.h>",
    "#include \"../source/advikku_global.h\"",
    "//converted by Nikku4211's furtoadvik.py, reliant on zumi.dxy's chipchune.py",
    "#include \"blank_raw.h\""
    ]
    
    for i in range(len(module.instruments)):
        if module.instruments[i].meta.type == InstrumentType.GBA_DMA:
            lines += ["#include \"%s_raw.h\"" % module.instruments[i].features[0].name]
            hlines += ["#include \"%s_raw.h\"" % module.instruments[i].features[0].name]
    
    lines += ["",
    "#define END 0xff",
    "#define HOLD 0xfe",
    "",
    "//speed",
    "//version",
    "//channels",
    "//song length in orders per channel",
    "//song order loopstart",
    "//commands linger flag",
    "//use subpatterns flag",
    "",
    "const uint8_t %sSongHeader[] = {" % title
    ]
    
    hlines += ["extern const uint8_t %sSongHeader[];" % title]
    
    lines += ["  0x%02x," % (module.subsongs[0].speed_pattern[0])]
    lines += ["  0x01,"]
    lines += ["  0x%02x," % module.get_num_channels()]
    lines += ["  0x%02x," % len(module.subsongs[0].order[0])]
    lines += ["  0x00,",
    "  0x01,",
    "  0x00"
    ]
    lines += ["};", ""]
    
    advikpattern = []
    advikorder = []
    
    if sfx == False:
        advikorder += ["const uint8_t * const %sSong[] = {" % title]
        
        furpatternlist = []
        
        for i in range(len(module.subsongs[0].order[0])):
            for chan_num in range(module.get_num_channels()):
                order = module.subsongs[0].order[chan_num]
            
                avail_patterns = list(filter(
                    lambda x: (
                        x.channel == chan_num and
                        x.subsong == 0
                    ),
                    module.patterns
                ))
                
                try:
                    p = avail_patterns[order[i]]
                    print(p)
                except:
                    continue
                    
                if daconly == True and chan_num == 0:
                    advikorder += [
                    "%sSongOrderBlank," % title
                    ]
                advikorder += [
                "%sSongOrderChan%d_%d," % (title, chan_num, order[i])
                ]
                
                if [chan_num, order[i]] not in furpatternlist:
                    
                    advikpattern += ["const uint8_t %sSongOrderChan%d_%d[] = {" % (title, chan_num, p.index)]
                    hlines += ["extern const uint8_t %sSongOrderChan%d_%d[];" % (title, chan_num, p.index)]
                    for d in p.data:
                        if not (
                        d.note == Note.OFF or
                        d.note == Note.OFF_REL or
                        d.note == Note.REL or
                        d.note == Note.__
                        ) and d.octave >= 2:
                            advikpattern += ["%d, %d," % (note_to_absolute[d.note]+((d.octave-2)*12), d.instrument+1)]
                        else:
                            advikpattern += ["HOLD, 0,"]
                            
                        if not (
                        d.note == Note.OFF or
                        d.note == Note.OFF_REL or
                        d.note == Note.REL
                        ):
                            if d.volume == 0xffff:
                                match d.effects[0][0]:
                                        case 0xEC:
                                            advikpattern += ["0x0E, 0x%02x," % d.effects[0][1]]
                                        case 0xED:
                                            advikpattern += ['0x07, 0x%02x,' % d.effects[0][1]]
                                        case 0x08:
                                            advikpattern += ['0x80, 0x%02x,' % d.effects[0][1]]
                                        case 0x00 | 0x01 | 0x02 | 0x03 | 0x04 | 0x0b | 0x0d | 0x0f:
                                            advikpattern += ['0x%02x, 0x%02x,' % (d.effects[0][0], d.effects[0][1])]
                                        case _:
                                            advikpattern += ['0x00, 0x00,']
                            else:
                                if chan_num != 2 and chan_num < 4:
                                    advikpattern += ['0x0C, 0x%02x,' % (d.volume)]
                                elif chan_num == 2:
                                    match d.volume:
                                        case 0 | 1 | 2 | 3:
                                            advikpattern += ['0x0C, 0x%02x,' % (0 << 4)]
                                        case 4 | 5 | 6 | 7:
                                            advikpattern += ['0x0C, 0x%02x,' % (6 << 4)]
                                        case 8 | 9 | 10 | 11:
                                            advikpattern += ['0x0C, 0x%02x,' % (4 << 4)]
                                        case 12 | 13 | 14:
                                            advikpattern += ['0x0C, 0x%02x,' % (8 << 4)]
                                        case _:
                                            advikpattern += ['0x0C, 0x%02x,' % (2 << 4)]
                                else:
                                    advikpattern += ['0x0C, 0x%02x,' % ((d.volume + 1) & 1)]
                        else:
                            advikpattern += ['0x0E, 0x01,']
                        #print(p.index)
                    advikpattern += ["END","};"]
                furpatternlist.append([chan_num, order[i]])
        
        advikorder += ["};", ""]
    else:
        order = module.subsongs[0].order[sfx_chan]
            
        advikpattern += ["const uint8_t %sSongOrderChan%d_%d[] = {" % (title, sfx_chan, order[0])]
        hlines += ["extern const uint8_t %sSongOrderChan%d_%d[];" % (title, sfx_chan, order[0])]
        for d in module.patterns[sfx_chan].data:
            if not (
            d.note == Note.OFF or
            d.note == Note.OFF_REL or
            d.note == Note.REL or
            d.note == Note.__
            ) and d.octave >= 2:
                advikpattern += ["%d, %d," % (note_to_absolute[d.note]+((d.octave-2)*12), d.instrument+1)]
            else:
                advikpattern += ["HOLD, 0,"]
                
            if not (
            d.note == Note.OFF or
            d.note == Note.OFF_REL or
            d.note == Note.REL
            ):
                if d.volume == 0xffff:
                    match d.effects[0][0]:
                            case 0xEC:
                                advikpattern += ["0x0E, 0x%02x," % d.effects[0][1]]
                            case 0xED:
                                advikpattern += ['0x07, 0x%02x,' % d.effects[0][1]]
                            case 0x08:
                                advikpattern += ['0x80, 0x%02x,' % d.effects[0][1]]
                            case 0x00 | 0x01 | 0x02 | 0x03 | 0x04 | 0x0b | 0x0d | 0x0f:
                                advikpattern += ['0x%02x, 0x%02x,' % (d.effects[0][0], d.effects[0][1])]
                            case _:
                                advikpattern += ['0x00, 0x00,']
                else:
                    if chan_num != 2 and chan_num < 4:
                        advikpattern += ['0x0C, 0x%02x,' % (d.volume)]
                    elif chan_num == 2:
                        match d.volume:
                            case 0 | 1 | 2 | 3:
                                advikpattern += ['0x0C, 0x%02x,' % (0 << 4)]
                            case 4 | 5 | 6 | 7:
                                advikpattern += ['0x0C, 0x%02x,' % (6 << 4)]
                            case 8 | 9 | 10 | 11:
                                advikpattern += ['0x0C, 0x%02x,' % (4 << 4)]
                            case 12 | 13 | 14:
                                advikpattern += ['0x0C, 0x%02x,' % (8 << 4)]
                            case _:
                                advikpattern += ['0x0C, 0x%02x,' % (2 << 4)]
                    else:
                        advikpattern += ['0x0C, 0x%02x,' % ((d.volume + 1) & 1)]
            else:
                advikpattern += ['0x0E, 0x01,']
        advikpattern += ["END","};"]
    
    #print(furpatternlist)
    if daconly == True and sfx == False:
        lines += ["const uint16_t %sSongOrderBlank[] = {" % title]
        hlines += ["extern const uint16_t %sSongOrderBlank[];" % title]
        
        for i in range(module.subsongs[0].pattern_length):
            lines += ["HOLD, 0, 0x00, 0x00,"]
        
        lines += ["END","};", ""]
    
    hlines += ["extern const uint8_t * const %sSong[];" % title]
    
    lines += advikpattern
    
    lines += advikorder
    
    lines += [""]
    
    for i in range(len(module.wavetables)):
        if not (
        module.wavetables[i].meta.height == 16 and module.wavetables[i].meta.width == 32
        or module.wavetables[i].meta.height == 16 and module.wavetables[i].meta.width == 64
        ):
            print("Wavetable either too long or too tall. Ignoring.")
        else:
            lines += ["const uint16_t %sWaveform%d[] = {" % (title, i)]
            hlines += ["extern const uint16_t %sWaveform%d[];" % (title, i)]
            
            for halfword in range(len(module.wavetables[i].data) >> 2):
                lines += ["0x%04x, " % (module.wavetables[i].data[halfword << 2] | (module.wavetables[i].data[(halfword << 2) + 1] << 4) | (module.wavetables[i].data[(halfword << 2) + 2] << 8) | (module.wavetables[i].data[(halfword << 2) + 3] << 12))]
                
            lines += ["};", ""]
    
    lines += ["const uint16_t %sWaveformBlank[] = {" % title]
    hlines += ["extern const uint16_t %sWaveformBlank[];" % title]
    lines += ["0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000"]
    lines += ["};", ""]
    
    lines += ["const uint16_t %sSquareInstruments[] = {" % title]
    hlines += ["extern const uint16_t %sSquareInstruments[];" % title]
    
    sqinstruments = [""] * len(module.instruments)
    
    for i in range(len(module.instruments)):
        if not (
        module.instruments[i].meta.type == InstrumentType.GB
        or module.instruments[i].meta.type == InstrumentType.GBA_DMA
        ):
            print("Instrument isn't for either GB PSG or GB DMA (without softmixing). Ignoring.")
            sqinstruments[i] = "0,"
        elif module.instruments[i].meta.type == InstrumentType.GB:
            sqinstruments[i] = "SSQR_LEN(0) | SSQR_TIME(2) | SSQR_IVOL(15) | SSQR_INC |"
            for feat in module.instruments[i].features:
                if isinstance(feat, datype.InsFeatureGB):
                    sqinstruments[i] = sqinstruments[i].replace("SSQR_LEN(0) | SSQR_TIME(2) | SSQR_IVOL(15) | SSQR_INC |", "")
                    sqinstruments[i] += "SSQR_LEN(%d) | SSQR_TIME(%d) | SSQR_IVOL(%d) |" % (64-feat.sound_len, feat.env_len, feat.env_vol)
                    match feat.env_dir:
                        case 0:
                            sqinstruments[i] += "SSQR_INC |"
                        case _:
                            sqinstruments[i] += "SSQR_DEC |"
                if isinstance(feat, datype.InsFeatureMacro):
                    for imacro in feat.macros:
                        if imacro.kind == MacroCode.DUTY and imacro.type == MacroType.SEQUENCE:
                            #print(imacro.data[0])
                            match imacro.data[0]:
                                case 0:
                                    sqinstruments[i] += "SSQR_DUTY1_8 |"
                                case 1:
                                    sqinstruments[i] += "SSQR_DUTY1_4 |"
                                case 2:
                                    sqinstruments[i] += "SSQR_DUTY1_2 |"
                                case 3:
                                    sqinstruments[i] += "SSQR_DUTY3_4 |"
            #print(sqinstruments[i] + str(i))
            sqinstruments[i] += "0,"
            #print(sqinstruments[i])
        else:
            sqinstruments[i] = "0,"
            
    lines += ["%s" % "\n".join(sqinstruments)]
    
    lines += ["};", ""]
    
    lines += ["const uint16_t %sWaveInstruments[] = {" % title]
    hlines += ["extern const uint16_t %sWaveInstruments[];" % title]
    
    for i in range(len(module.instruments)):
        if module.instruments[i].meta.type == InstrumentType.GB:
            waveplaylength = 0
            for feat in module.instruments[i].features:
                waveplaylength = 0
                if isinstance(feat, datype.InsFeatureGB):
                    waveplaylength = 256-feat.sound_len
                    lines += ["SWAV_LEN(%d) | " % (64-feat.sound_len)]
                    match feat.env_vol:
                        case 0 | 1 | 2 | 3:
                            advikpattern += ["SWAV_VOL0 |"]
                        case 4 | 5 | 6 | 7:
                            advikpattern += ["SWAV_VOL25 |"]
                        case 8 | 9 | 10 | 11:
                            advikpattern += ["SWAV_VOL50 |"]
                        case 12 | 13 | 14:
                            advikpattern += ["SWAV_VOL75 |"]
                        case _:
                            advikpattern += ["SWAV_VOL100 |"]
            lines += ["0,"]
            match waveplaylength:
                case 0:
                    lines += ["SWAV_LEN_OFF,"]
                case _:
                    lines += ["SWAV_LEN_ON,"]
        else:
            lines += ["0, SWAV_LEN_OFF,"]
    
    lines += ["};", ""]
    
    lines += ["const uint16_t * const %sWaveforms[] = {" % title]
    hlines += ["extern const uint16_t * const %sWaveforms[];" % title]
    
    advikwaveform = [""] * len(module.instruments)
    
    for i in range(len(module.instruments)):
        if module.instruments[i].meta.type == InstrumentType.GB:
            advikwaveform[i] = "%sWaveformBlank," % title
            for feat in module.instruments[i].features:
                if isinstance(feat, datype.InsFeatureMacro):
                    for imacro in feat.macros:
                        if imacro.kind == MacroCode.WAVE and imacro.type == MacroType.SEQUENCE:
                            if imacro.data[0] > 0:
                                advikwaveform[i] = "%sWaveform%d," % (title, imacro.data[0]-1)
                            else:
                                advikwaveform[i] = "%sWaveform0," % title
        else:
            advikwaveform[i] = "%sWaveformBlank," % title
            
    lines += ["%s" % "\n".join(advikwaveform)]
    
    lines += ["};", ""]
    
    noiseinstruments = [""] * len(module.instruments)
    
    lines += ["const uint16_t %sNoiseInstruments[] = {" % title]
    hlines += ["extern const uint16_t %sNoiseInstruments[];" % title]
    
    for i in range(len(module.instruments)):
        if module.instruments[i].meta.type == InstrumentType.GB:
            noiseinstruments[i] = "SSQR_LEN(0) | SSQR_TIME(2) | SSQR_IVOL(15) | SSQR_INC | SNOI_LONG_PACK | "
            for feat in module.instruments[i].features:
                if isinstance(feat, datype.InsFeatureGB):
                    noiseinstruments[i] = "SSQR_LEN(%d) | SSQR_TIME(%d) | SSQR_IVOL(%d) | SNOI_LONG_PACK | " % (64-feat.sound_len, feat.env_len, feat.env_vol)
                    match feat.env_dir:
                        case 0:
                            noiseinstruments[i] += "SSQR_INC | "
                        case _:
                            noiseinstruments[i] += "SSQR_DEC | "
                if isinstance(feat, datype.InsFeatureMacro):
                    for imacro in feat.macros:
                        if imacro.kind == MacroCode.DUTY and imacro.type == MacroType.SEQUENCE:
                            noiseinstruments[i] = noiseinstruments[i].replace("SNOI_LONG_PACK | ", "")
                            match imacro.data[0]:
                                case 0:
                                    noiseinstruments[i] += "SNOI_LONG_PACK |"
                                case _:
                                    noiseinstruments[i] += "SNOI_SHORT_PACK |"
                            #print(imacro.kind)
                            #print(imacro.data[0])
                
            noiseinstruments[i] += "0,"
        else:
            noiseinstruments[i] = "0,"
    
    lines += ["%s" % "\n".join(noiseinstruments)]
    
    lines += ["};", ""]
    
    lines += ["const uint8_t * const %sDMAInstruments[] = {" % title]
    hlines += ["extern const uint8_t * const %sDMAInstruments[];" % title]
    
    adviksample = [""] * len(module.instruments)
    
    for i in range(len(module.instruments)):
        if module.instruments[i].meta.type == InstrumentType.GBA_DMA:
            adviksample[i] = "%s_raw," % module.instruments[i].features[0].name
        else:
            adviksample[i] = "blank_raw,"
            
    lines += ["%s" % "\n".join(adviksample)]
    
    lines += ["};", ""]
    
    lines += ["const uint16_t %sDMADurations[] = {" % title]
    hlines += ["extern const uint16_t %sDMADurations[];" % title]
    
    for i in range(len(module.instruments)):
        if module.instruments[i].meta.type == InstrumentType.GBA_DMA:
            for feat in module.instruments[i].features:
                if isinstance(feat, datype.InsFeatureMacro):
                    for imacro in feat.macros:
                        if imacro.kind == MacroCode.VOL and imacro.type == MacroType.SEQUENCE:
                            volframe = 0
                            for voldatum in imacro.data:
                                volframe += 1
                                if voldatum == 0:
                                    lines += ["%d," % (volframe - 1)]
                                    break
        else:
            lines += ["0,"]
    
    lines += ["};", ""]
    
    if sfx == False:
        lines += ["const advikSongStruct %sSongStruct = {" % title,
        "%sSong," % title,
        "%sSongHeader," % title,
        "%sSquareInstruments," % title,
        "%sWaveInstruments," % title,
        "%sWaveforms," % title,
        "%sNoiseInstruments," % title,
        "%sDMAInstruments," % title,
        "%sDMADurations" % title,
        "};"]
        
        hlines += ["extern const advikSongStruct %sSongStruct;" % title]
    else:
        lines += ["const advikSFXStruct %sSFXStruct = {" % title,
        "%sSongOrderChan%d_0," % (title, sfx_chan),
        "%sSongHeader," % title,
        "%sSquareInstruments," % title,
        "%sWaveInstruments," % title,
        "%sWaveforms," % title,
        "%sNoiseInstruments," % title,
        "%sDMAInstruments," % title,
        "%sDMADurations" % title,
        "};"]
        
        hlines += ["extern const advikSFXStruct %sSFXStruct;" % title]
    
    return lines, hlines

def main(argv):
    if len(argv) >= 2 and argv[1] in ("--help", "-h"):
        print("use like this: %s INFILE OUTFILE --sfx CHANNEL" % argv[0])
    elif len(argv) < 3:
        print("Too few arguments. Need --help?")
        sys.exit(1)
    else:
        module = FurnaceModule(argv[1])
        #print("\n".join(fur2adv(module, "AdvikConv", argv[2])))
        advikresult = open(argv[2],"wt")
        advikresulth = open((argv[2].split(".")[0]+".h"),"wt")
        if len(argv) >= 5:
            advikresult.write("\n".join(fur2adv(module, True, int(argv[4]))[0]))
            advikresulth.write("\n".join(fur2adv(module, True, int(argv[4]))[1]))
        else:
            advikresult.write("\n".join(fur2adv(module, False, 0)[0]))
            advikresulth.write("\n".join(fur2adv(module, False, 0)[1]))
        advikresult.close()
        advikresulth.close()
        print(argv[2],"compiled succesfully.")
    

if __name__=='__main__':
    main(sys.argv)