#include <iostream>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <vector>

void MusicPlay(sf::Music & music){
    music.openFromFile("Music/echoes.wav");//загружаем файл
    music.setVolume(100);
    music.play();
};

void MusicON(sf::Music & music, int & i){
    music.stop();
    std::vector<std::string> MBASE = {"Music/echoes.wav", "Music/end.wav", "Music/riders.wav", "Music/space.wav", "Music/jesus.wav", "Music/starman.wav"};
    music.openFromFile(MBASE[i]);//загружаем файл
    music.setVolume(50);
    music.play();
    ++i;
    if (i==6) i = 0;
}

void MOVING (Player a, sf::Sound & soundMOVE) {
    if (soundMOVE.getStatus() == sf::SoundSource::Stopped) {
        if (a.v > a.vmax/10) {
            soundMOVE.setVolume(30);
            soundMOVE.play();
        }
    }
    if (soundMOVE.getStatus() == sf::SoundSource::Playing) {
        if (a.v < a.vmax/10) {
            soundMOVE.stop();
        }
    }
}
