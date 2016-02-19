using System;
using System.Collections.Generic;
using System.IO;
using System.Reflection;
using NAudio.Wave;
using NAudio.Wave.SampleProviders;

namespace CollisionFeedbackDemo
{
    class Sound : IDisposable
    {
        public WaveFileReader WaveReader { get; }
        public WaveChannel32 WaveChannel { get; }

        public Sound(string filename)
        {
            var assembly = Assembly.GetExecutingAssembly();
            string assemblyName = assembly.GetName().Name;
            byte[] sound;
            using (var stream = assembly.GetManifestResourceStream(string.Format($"{assemblyName}.{filename}")))
            {
                sound = new byte[stream.Length];
                stream.Read(sound, 0, (int)stream.Length);
            }
            var soundStream = new MemoryStream(sound);
            WaveReader = new WaveFileReader(soundStream);
            WaveChannel = new WaveChannel32(WaveReader) { PadWithZeroes = false };
        }

        protected virtual void Dispose(bool disposing)
        {
            if (disposing)
            {
                WaveChannel.Dispose();
                WaveReader.Dispose();
            }
        }

        public void Dispose()
        {
            Dispose(true);
        }
    }

    class AudioEngine : IDisposable
    {
        MixingSampleProvider _mixer;
        DirectSoundOut _audioOutput;
        Dictionary<string, Sound> _sounds = new Dictionary<string, Sound>();

        public AudioEngine()
        {
            LoadSound("can.wav");
            LoadSound("metal.wav");
            LoadSound("plastic.wav");
            LoadSound("rubber.wav");

            _mixer = new MixingSampleProvider(WaveFormat.CreateIeeeFloatWaveFormat(44100, 2));
            _mixer.ReadFully = true;
            _audioOutput = new DirectSoundOut();
            _audioOutput.Init(_mixer);
            _audioOutput.Play();
        }

        public void LoadSound(string filename)
        {
            var sound = new Sound(filename);
            _sounds.Add(filename, sound);
        }

        public void Play(string filename)
        {
            var sound = _sounds[filename];
            sound.WaveReader.Position = 0;
            _mixer.AddMixerInput(sound.WaveChannel);
        }

        public void SetVolume(string filename, float volume)
        {
            _sounds[filename].WaveChannel.Volume = volume;
        }

        protected virtual void Dispose(bool disposing)
        {
            if (disposing)
            {
                _audioOutput.Dispose();

                foreach (var sound in _sounds.Values)
                {
                    sound.Dispose();
                }
            }
        }

        public void Dispose()
        {
            Dispose(true);
        }
    }
}
