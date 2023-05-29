#pragma once

#include <SFML/Audio.hpp>
#include <iostream>
#include "Parameters.h"
#include "Exceptions.h"

enum Sound{
    WIN_SOUND,
    LOSE_SOUND,
    MOVE_SOUND
};

enum Music{
    MENU,
    LEVEL
};

class AudioManager
{
private:

    /** Contains loaded from file sounds*/
    std::vector<sf::SoundBuffer> _buffers;

    /** Contains sf::Sound objects that can play the sound*/
    std::vector<sf::Sound> _sounds;

    /** Is able to play menu music from file*/
    sf::Music _menu_music;

    /** Is able to play level music from file*/
    sf::Music _level_music;

public:

    AudioManager();

    /** Creates all sound related objects in program*/
    void SetupSoundsAndMusic();

    /** Plays chosen music*/
    void PlayMusic(Music music);

    /** Plays chosen sound effect*/
    void PlaySound(Sound sound);

    /** Chosen music stops playing*/
    void StopMusic(Music music);

    /** Chosen sound stops playing*/
    void StopSound(Sound sound);

    /** Check if the music is playing at current moment*/
    bool IsPlaying(Music music) const;

};