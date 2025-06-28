/*
** EPITECH PROJECT, 2025
** Projet
** File description:
** SFMLRenderer.cpp
*/

#include "SFMLSound.hpp"
    #include <iostream>

namespace sfml
{
    SFMLSound::SFMLSound(const sf::SoundBuffer &buffer)
    {
        _sound.setBuffer(buffer);
    }

    SFMLSound::~SFMLSound()
    {
        _sound.stop();
    }

    void SFMLSound::play(bool loop)
    {
        _sound.setLoop(loop);
        _sound.play();
        _paused = false;
    }

    void SFMLSound::pause()
    {
        _sound.pause();
        _paused = true;
    }

    void SFMLSound::changeState()
    {
        std::cout << "lenrlf" << std::endl;
        if (_paused)
            _sound.play();
        else
            _sound.pause();
        _paused = !_paused;
    }

    void SFMLSound::stop()
    {
        _sound.stop();
        _paused = true;
    }

    void SFMLSound::reset()
    {
        _sound.setPlayingOffset(sf::Time::Zero);
    }
}
