#include "App.h"
#include "Audio.h"

#include "Defs.h"
#include "Log.h"

// NOTE: Recommended using: Additional Include Directories,
// instead of 'hardcoding' library location path in code logic
#include "SDL/include/SDL.h"
#include "SDL_mixer/include/SDL_mixer.h"
#include <iostream>
using namespace std;

// NOTE: Library linkage is configured in Linker Options
//#pragma comment(lib, "../Game/Source/External/SDL_mixer/libx86/SDL2_mixer.lib")

Audio::Audio(bool start_enabled) : Module(start_enabled)
{
	music = NULL;
	name.Create("audio");
}

// Destructor
Audio::~Audio()
{}

// Called before render is available
bool Audio::Awake(pugi::xml_node& config)
{
	LOG("Loading Audio Mixer");
	bool ret = true;
	SDL_Init(0);

	if (SDL_InitSubSystem(SDL_INIT_AUDIO) < 0)
	{
		LOG("SDL_INIT_AUDIO could not initialize! SDL_Error: %s\n", SDL_GetError());
		active = false;
		ret = true;
	}

	int flags = MIX_INIT_OGG && MIX_INIT_MP3 && MIX_INIT_FLAC;
	int init = Mix_Init(flags);

	if ((init & flags) != flags)
	{
		LOG("Could not initialize Mixer lib. Mix_Init: %s", Mix_GetError());
		active = false;
		ret = true;
	}

	// Initialize SDL_mixer
	if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		LOG("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
		active = false;
		ret = true;
	}

	Mix_Volume(-1, SliderLevelFX);
	Mix_VolumeMusic(SliderLevelMusic);

	musicSourcePosition.x = 0;
	musicSourcePosition.y = 0;

	return ret;
}

bool Audio::Update(float dt)
{

	if (playMusicSpatially == false) Mix_VolumeMusic(SliderLevelMusic);
	if (playMusicSpatially == true) PlayMusicSpatially(musicSourcePosition);

	//Mix_Volume(-1, SliderLevelFX);

	return true;
}

// Called before quitting
bool Audio::CleanUp()
{
	if (!active)
		return true;

	LOG("Freeing sound FX, closing Mixer and Audio subsystem");

	if (music != NULL)
	{
		Mix_FreeMusic(music);
	}

	ListItem<Mix_Chunk*>* item;
	for (item = fx.start; item != NULL; item = item->next)
		Mix_FreeChunk(item->data);

	fx.clear();

	Mix_CloseAudio();
	Mix_Quit();
	SDL_QuitSubSystem(SDL_INIT_AUDIO);

	return true;
}

// Play a music file
bool Audio::PlayMusic(const char* path, float fadeInTime, float fadeOutTime)
{
	bool ret = true;

	if (!active)
		return false;

	if (music != NULL)
	{
		if (fadeOutTime > 0.0f)
		{
			Mix_FadeOutMusic(int(fadeOutTime * 1000.0f));
		}
		else
		{
			Mix_HaltMusic();

		}

		// this call blocks until fade out is done
		Mix_FreeMusic(music);
	}

	music = Mix_LoadMUS(path);

	if (music == NULL)
	{
		LOG("Cannot load music %s. Mix_GetError(): %s\n", path, Mix_GetError());
		ret = false;
	}
	else
	{

		if (fadeInTime > 0.0f)
		{
			if (Mix_FadeInMusic(music, -1, (int)(fadeInTime * 1000.0f)) < 0)
			{
				LOG("Cannot fade in music %s. Mix_GetError(): %s", path, Mix_GetError());
				ret = false;
			}
		}
		else
		{
			if (Mix_PlayMusic(music, -1) < 0)
			{
				LOG("Cannot play in music %s. Mix_GetError(): %s", path, Mix_GetError());
				ret = false;
			}
		}
	}

	LOG("Successfully playing %s", path);
	return ret;
}

// Load WAV
unsigned int Audio::LoadFx(const char* path)
{
	unsigned int ret = 0;

	if (!active)
		return 0;

	Mix_Chunk* chunk = Mix_LoadWAV(path);

	if (chunk == NULL)
	{
		LOG("Cannot load wav %s. Mix_GetError(): %s", path, Mix_GetError());
	}
	else
	{
		fx.add(chunk);
		ret = fx.count();
	}

	return ret;
}

// Play WAV
bool Audio::PlayFxSpatially(unsigned int id, iPoint soundGeneratorPosition, int channel, int repeat)
{
	bool ret = false;

	if (!active)
		return false;

	// Todo 3 (done): Finish the new PlayFx function to be able to play sound effects spatially
	int setChunkVolume = SliderLevelFX - (sqrt(pow(app->player->position.x - soundGeneratorPosition.x, 2) + pow(app->player->position.y - soundGeneratorPosition.y, 2)) / 8);

	if (setChunkVolume <= 0) setChunkVolume = 0;

	if (id > 0 && id <= fx.count())
	{
		Mix_VolumeChunk(fx[id - 1], setChunkVolume);

		Mix_PlayChannel(-1, fx[id - 1], repeat);
	}

	return ret;
}

// Play WAV
bool Audio::PlayFx(unsigned int id, int repeat)
{
	bool ret = false;

	if (!active)
		return false;

	if (id > 0 && id <= fx.count())
	{
		Mix_VolumeChunk(fx[id - 1], SliderLevelFX);

		Mix_PlayChannel(-1, fx[id - 1], repeat);
	}

	return ret;
}

bool Audio::ChangeMusic(int Id, float fadeInTime, float fadeOutTime)
{
	// Todo 1 (done): Complete the music switcher (an enumerator on Audio.h is given with all the playlist)
	switch (Id)
	{
	case OFF:
	{
		Mix_HaltMusic();
		break;
	}
	case BOSS_1:
	{
		Mix_ResumeMusic();

		app->audio->PlayMusic("Assets/Audio/Music/boss_1.ogg", fadeInTime, fadeOutTime);

		break;
	}
	case BOSS_2:
	{
		Mix_ResumeMusic();

		app->audio->PlayMusic("Assets/Audio/Music/boss_2.ogg", fadeInTime, fadeOutTime);

		break;
	}
	case BOSS_3:
	{
		Mix_ResumeMusic();

		app->audio->PlayMusic("Assets/Audio/Music/boss_3.ogg", fadeInTime, fadeOutTime);

		break;
	}
	case FINAL_BOSS:
	{
		Mix_ResumeMusic();

		app->audio->PlayMusic("Assets/Audio/Music/final_boss.ogg", fadeInTime, fadeOutTime);

		break;
	}
	case SHIP_DECK:
	{
		Mix_ResumeMusic();

		app->audio->PlayMusic("Assets/Audio/Music/final_zone_C.ogg", fadeInTime, fadeOutTime);

		break;
	}
	case CAVE:
	{
		Mix_ResumeMusic();

		app->audio->PlayMusic("Assets/Audio/Music/cave_zone_passthrough_V2.ogg", fadeInTime, fadeOutTime);

		break;
	}
	case BASE:
	{
		Mix_ResumeMusic();

		app->audio->PlayMusic("Assets/Audio/Music/military_lab_zone_B.ogg", fadeInTime, fadeOutTime);

		break;
	}
	case MAIN_MAP:
	{
		Mix_ResumeMusic();

		app->audio->PlayMusic("Assets/Audio/Music/road_zone_mainHub.ogg", fadeInTime, fadeOutTime);

		break;
	}
	case MAIN_MAP_AT_NIGHT:
	{
		Mix_ResumeMusic();

		app->audio->PlayMusic("Assets/Audio/Music/road_zone_mainHub_night.mp3", fadeInTime, fadeOutTime);

		break;
	}
	case MAIN_MAP_SUNRISE:
	{
		Mix_ResumeMusic();

		app->audio->PlayMusic("Assets/Audio/Music/final_zone_C.ogg", fadeInTime, fadeOutTime);

		break;
	}
	case MOTEL_ZONE:
	{
		Mix_ResumeMusic();

		app->audio->PlayMusic("Assets/Audio/Music/motel_zone_A.ogg", fadeInTime, fadeOutTime);

		break;
	}
	case TENSION_PUZZLE_1:
	{
		Mix_ResumeMusic();

		app->audio->PlayMusic("Assets/Audio/Music/tension_puzzle_1.ogg", fadeInTime, fadeOutTime);

		break;
	}
	case RADIO_ITEM_MUSIC:
	{
		Mix_ResumeMusic();

		app->audio->PlayMusic("Assets/audio/music/radio_item_music.ogg", fadeInTime, fadeOutTime);

		break;
	}
	case STORY_INTRO:
	{
		Mix_ResumeMusic();

		app->audio->PlayMusic("Assets/Audio/Music/story_introduction.ogg", fadeInTime, fadeOutTime);

		break;
	}
	case STORY_NOTE:
	{
		Mix_ResumeMusic();

		app->audio->PlayMusic("Assets/Audio/Music/story_note.ogg", fadeInTime, fadeOutTime);

		break;
	}
	case STORY_COMPUTER:
	{
		Mix_ResumeMusic();

		app->audio->PlayMusic("Assets/Audio/Music/story_computer.ogg", fadeInTime, fadeOutTime);

		break;
	}
	case STORY_FINAL_BOSS_APPEARS:
	{
		Mix_ResumeMusic();

		app->audio->PlayMusic("Assets/Audio/Music/final_boss_appears.ogg", fadeInTime, fadeOutTime);

		break;
	}
	case STORY_BAD_ENDING:
	{
		Mix_ResumeMusic();

		app->audio->PlayMusic("Assets/Audio/Music/story_bad_ending.ogg", fadeInTime, fadeOutTime);

		break;
	}
	case STORY_GOOD_ENDING:
	{
		Mix_ResumeMusic();

		app->audio->PlayMusic("Assets/Audio/Music/story_good_ending.ogg", fadeInTime, fadeOutTime);

		break;
	}
	case LOGO_INTRO:
	{
		Mix_ResumeMusic();

		app->audio->PlayMusic("Assets/Audio/Music/logoMusicV2.ogg", fadeInTime, fadeOutTime);

		break;
	}
	case TITLE_THEME:
	{
		Mix_ResumeMusic();

		app->audio->PlayMusic("Assets/Audio/Music/mainTitleMusic.ogg", fadeInTime, fadeOutTime);

		break;
	}
	case CREDITS_THEME:
	{
		Mix_ResumeMusic();

		app->audio->PlayMusic("Assets/Audio/Music/creditsSong.ogg", fadeInTime, fadeOutTime);

		break;
	}
	case MENU:
	{
		Mix_ResumeMusic();

		app->audio->PlayMusic("Assets/Audio/Music/menu.ogg", fadeInTime, fadeOutTime);

		break;
	}
	case PAUSE_MENU:
	{
		Mix_ResumeMusic();

		app->audio->PlayMusic("Assets/Audio/Music/pauseMenuMusic.ogg", fadeInTime, fadeOutTime);

		break;
	}
	}

	return true;
}

bool Audio::PlayMusicSpatially(iPoint musicGeneratorPosition)
{
	// Todo 2 (done): Complete the function to be able to play music tracks spatially
	int setMusicVolume = SliderLevelMusic - (sqrt(pow(app->player->position.x - musicGeneratorPosition.x, 2) + pow(app->player->position.y - musicGeneratorPosition.y, 2)) / 8);

	if (setMusicVolume <= 0) setMusicVolume = 0;

	Mix_VolumeMusic(setMusicVolume);

	return true;
}
