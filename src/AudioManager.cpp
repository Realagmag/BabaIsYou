#include "AudioManager.h"

AudioManager::AudioManager()
{
    SetupSoundsAndMusic();
}

void AudioManager::SetupSoundsAndMusic()
{
    sf::SoundBuffer win_buffer;
    if(!win_buffer.loadFromFile("../sounds/win.wav"))
    {
        std::cerr<<"Failed to load from file win.wav"<<std::endl;
    }
    _buffers.emplace_back(win_buffer);

    sf::SoundBuffer lose_buffer;
    if(!lose_buffer.loadFromFile("../sounds/lose.wav"))
    {
        std::cerr<<"Failed to load from file lose.wav"<<std::endl;
    }
    _buffers.emplace_back(lose_buffer);


    sf::SoundBuffer move_buffer;
    if(!move_buffer.loadFromFile("../sounds/move.wav"))
    {
        std::cerr<<"Failed to load from file move.wav"<<std::endl;
    }
    _buffers.emplace_back(move_buffer);


    sf::Sound win_sound(_buffers[WIN_SOUND]);
    win_sound.setVolume(100);
    _sounds.emplace_back(win_sound);

    sf::Sound lose_sound(_buffers[LOSE_SOUND]);
    lose_sound.setVolume(100);
    _sounds.emplace_back(lose_sound);

    sf::Sound move_sound(_buffers[MOVE_SOUND]);
    move_sound.setVolume(100);
    _sounds.emplace_back(move_sound);

    if(!_menu_music.openFromFile("../sounds/menumusic.ogg"))
    {
        std::cerr<<"Failed to load menumusic.ogg"<<std::endl;
    };
    _menu_music.setLoop(true);

    if(!_level_music.openFromFile("../sounds/levelmusic.ogg"))
    {
        std::cerr<<"Failed to load levelmusic.ogg"<<std::endl;
    }
    _level_music.setLoop(true);
}

void AudioManager::PlayMusic(Music music)
{
    if (music == MENU) _menu_music.play();
    else if (music == LEVEL) _level_music.play();
}

void AudioManager::PlaySound(Sound sound)
{
    _sounds[sound].play();
}

void AudioManager::StopMusic(Music music)
{
    if (music == MENU) _menu_music.stop();
    else if (music == LEVEL) _level_music.stop();
}

void AudioManager::StopSound(Sound sound)
{
    _sounds[sound].stop();
}

bool AudioManager::IsPlaying(Music music)
{
    if (music == MENU)
    {
        sf::SoundSource::Status status = _menu_music.getStatus();
        if (status == sf::Music::Playing) {return true;}
        else {return false;}
    }
    else if (music == LEVEL){
        sf::SoundSource::Status status = _level_music.getStatus();
        if (status == sf::Music::Playing) {return true;}
        else {return false;}
    }
}

bool AudioManager::IsPlaying(Sound sound)
{
    sf::SoundSource::Status status = _sounds[sound].getStatus();
    if (status == 2) {return true;}
    else {return false;}
}