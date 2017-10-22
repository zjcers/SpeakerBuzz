As of Oct 19, there are several hardcoded values in the SPI driver (namely, the frame length and bit rate).
Conveniently, the values picked line up perfectly with the DAC8311, so for right now, it's good enough (tm).

According to the DAC8311 datasheet, the first two bits of the word that it written to it are the "mode".
This mode is 0b00 for normal operation. Other values are for various power-down states. Most significant bit 
goes first (shift register). ~SYNC is held HIGH until it is time to send a word. ~SYNC is held LOW for 
16 falling edges of the clock signal and then set back to HIGH to update the DAC. If 16 cycles do not
pass before ~SYNC is reasserted, the invalid word is discarded.

The datasheet for the Audio BoosterPack says that the speaker is driven by a TI TPA301 amplifier. The amp 
is enabled by setting AMP ON to low (Tiva pin PP3).

If the SSI peripherial of the Tiva is put into Advanced mode or higher, the frame signal lines up perfectly 
with what the DAC requires. This might be a good thing to try after the first version is working.