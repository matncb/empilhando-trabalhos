#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <playlist.h>
#include <poplist.h>
#include <graph.h>
#include <music.h>

char *nameBank[] = {
    "Ana", "Bruno", "Carla", "Daniel", "Elisa", "Felipe", "Gabriela",
    "Hugo", "Isabela", "Joao", "Laura", "Marcos", "Natalia", "Otavio",
    "Patricia", "Rafael", "Sofia", "Thiago", "Ursula", "Vitor",
    "Alice", "Bernardo", "Clara", "Davi", "Ester", "Fabio", "Giovana"
};

char *songBank[] = {
    "Bohemian Rhapsody",
    "Stairway to Heaven",
    "Smells Like Teen Spirit",
    "Hotel California",
    "Imagine",
    "Like a Rolling Stone",
    "Hey Jude",
    "Billie Jean",
    "Wonderwall",
    "Sweet Child o' Mine",
    "Shape of You",
    "Blinding Lights",
    "Someone Like You",
    "Yesterday",
    "Rolling in the Deep",
    "Take On Me",
    "Africa",
    "Don't Stop Believin'",
    "Another Brick in the Wall pt 2",
    "Thriller"};

int main()
{
    int vertex_qnt = 10;
    int musics_qnt = 10;

    Graph *graph = graph_create(vertex_qnt);
    PopList *poplist = poplist_create();

    if ((!graph) || (!poplist))
        return 1;

    int bankSize = sizeof(songBank) / sizeof(songBank[0]);

    for (int i = 0; i <= vertex_qnt; i++)
    {
        Person *person = person_create(nameBank[i], "312312312321", "john_doe@email.com");
        poplist_add(poplist, person);

        PlayList *playlist = playlist_create();
        for (int j = 0; j <= musics_qnt; j++)
        {

            srand(time(NULL));
            int randomIndex = rand() % bankSize;

            Music *music = music_create(songBank[randomIndex], nameBank[j], "blablabla");
            playlist_add(playlist, music);
        }
        person_set_playlist(person, playlist);
    }
    return 0;
}