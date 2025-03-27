#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SONG 100
#define MAX_NAME 100
struct music
{
  int id;
  char name[MAX_NAME];
  char artist[MAX_NAME];
};

struct music playlist[MAX_SONG];
int musicCount = 0;

void saveToFile()
{
  FILE *file = fopen("playlist.txt", "w");
  if (file == NULL)
  {
    printf("Error saving file!\n");
    return;
  }
  for (int i = 0; i < musicCount; i++)
  {
    {
      fprintf(file, "%d|%s|%s\n", playlist[i].id, playlist[i].name, playlist[i].artist);
    }

    fclose(file);
    printf("Playlist saved successfully!\n");
  }
}

void loadFromFile()
{
  FILE *file = fopen("playlist.txt", "r");
  if (file == NULL)
    return;
  musicCount = 0;
  while (fscanf(file, "%d|%[^|]|%[^\n]\n", &playlist[musicCount].id, playlist[musicCount].name, playlist[musicCount].artist) != EOF)
  {
    musicCount++;
  }
  fclose(file);
}

void AddMusic()
{
  if (musicCount >= MAX_SONG)
  {
    printf("Playlist is Full!\n");
    return;
  }
  printf("Enter music details: ");
  scanf("%d", &playlist[musicCount].id);
  getchar();

  printf("Music name: ");
  fgets(playlist[musicCount].name, MAX_NAME, stdin);
  playlist[musicCount].name[strcspn(playlist[musicCount].name, "\n")] = '\0';

  printf("Artist name: ");
  fgets(playlist[musicCount].artist, MAX_NAME, stdin);
  playlist[musicCount].artist[strcspn(playlist[musicCount].artist, "\n")] = '\0';

  musicCount++;
  saveToFile();
}

void showMusic()
{
  if (musicCount == 0)
  {
    printf("No musics in the playlist");
    return;
  }
  printf("\nPlaylist:\n");
  for (int i = 0; i < musicCount; i++)
  {
    printf("%d. %s - %s\n", playlist[i].id, playlist[i].name, playlist[i].artist);
  }
}

void deleteMusic()
{
  if (musicCount == 0)
  {
    printf("No songs to delete:\n");
    return;
  }
  int id, found = 0;
  printf("Enter song ID to delete");
  scanf("%d", &id);

  for (int i = 0; i < musicCount; i++)
  {
    if (playlist[i].id == id)
    {
      found = 1;
      for (int j = i; j < musicCount; j++)
      {
        playlist[j] = playlist[j + 1];
        playlist[j].id = j + 1;
      }
      musicCount--;
      break;
    }
  }
  if (found)
  {
    saveToFile();
    printf("Music Deleted successfully!\n");
  }
  else
  {
    printf("Song not found!\n");
  }
}

int main()
{
  printf("\nOnly 100 songs details stored\n");
  loadFromFile();
  int choice;
  while (1)
  {
    printf("\n🎵 Music Playlist Manager 🎵\n");
    printf("1. Add Music\n");
    printf("2. Show Playlist\n");
    printf("3. Delete Song\n");
    printf("4. Exit\n");
    printf("Choose an option: ");
    scanf("%d", &choice);
    getchar(); // Clear buffer

    switch (choice)
    {
    case 1:
      AddMusic();
      break;
    case 2:
      showMusic();
      break;
    case 3:
      deleteMusic();
      break;
    case 4:
      printf("Exiting...\n");
      return 0;
    default:
      printf("❌ Invalid choice! Try again.\n");
    }
  }
  return 0;
}