import wave
import struct

def make_soundfile(sample, freq, fname):
    frate = 7000  # framerate as a float

    data_size = len(sample)

    sine_list = []
    for x in sample:
        sine_list.append(float(x) / 2 * 32768)

    wav_file = wave.open(fname + ".wav", "w")

    nchannels = 1
    sampwidth = 2
    framerate = int(frate)
    nframes = data_size
    comptype = "NONE"
    compname = "not compressed"

    wav_file.setparams((nchannels, sampwidth, framerate, nframes,
        comptype, compname))
    # now write out the file ...
    print( "may take a moment ..." )
    for s in sine_list:
        # write the audio frames to file
        wav_file.writeframes(struct.pack('h', int(s)))
    wav_file.close()
    print( "%s written" % fname )


for n in range(1, 11):
  fname = "test%02d.tst" % n
  print fname
  sample = open(fname).readlines()
  sample = sample[1:]
  freq = len(sample)
  make_soundfile(sample, freq, fname)
