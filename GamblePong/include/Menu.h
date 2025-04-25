#ifndef MENU_H
#define MENU_H

void DrawTitleScreen(void);
void UpdateTitleScreen(void);
void DrawGameScreen(void);
void UpdateGame(void);
void DrawPostGameMenu(const char *winnerText);
void HandlePostGameOptions(void);
void DrawControlsScreen(void);
void Credits(void);
void DrawModesMenu(void);
void UpdateModesMenu(void);
void DrawSetupPlay(void);
void UpdateSetupPlay(void);
void quickPlaySelector(void);




#endif // MENU_H
