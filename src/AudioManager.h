#pragma once

#include <SFML/Audio.hpp>
#include <iostream>

enum Sound{
    WIN_SOUND,
    LOSE_SOUND,
    MOVE_SOUND
};

enum Music{
    MENU,
    LEVEL
};

enum SoundStatus{
    STOPPED,
    PAUSED,
    PLAYING
};

class AudioManager
{
private:
    std::vector<sf::SoundBuffer> _buffers;
    std::vector<sf::Sound> _sounds;
    sf::Music _menu_music;
    sf::Music _level_music;

public:
    AudioManager();
    void SetupSoundsAndMusic();
    void PlayMusic(Music music);
    void PlaySound(Sound sound);
    void StopMusic(Music music);
    void StopSound(Sound sound);
    bool IsPlaying(Music music);
    bool IsPlaying(Sound sound);


};