# Advikku Demo
Demo for a WIP music engine for the Game Boy Advance that uses a cell-based custom format.

This music engine has been used in the GBA Jam game [Sleep Paradox](https://github.com/chrislewisdev/sleep-paradox).

## Building

Install DevkitARM, use its environment and run `make`.

### Dependencies
- Tonclib
- [DevkitARM (Which includes Tonclib)](https://devkitpro.org/wiki/Getting_Started)
- [PTexConv](https://github.com/Garhoogin/ptexconv)
- [ChipChune](https://github.com/ZoomTen/chipchune)

## Known Issues
- There is a huge bug where the music will mess up if it is changed while still playing. No workaround is known as of yet.
- Another huge bug where the sound effects will mess up the music. No workaround for now.

## Licence
This demo and the music engine is under the Boost Software Library licence. No attribution is needed for anything using this demo's code.
Graphics and music and sound effects are (c) 2024 Nikku4211.
