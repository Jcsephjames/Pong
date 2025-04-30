#ifndef CUSTOM_H
#define CUSTOM_H

#include "raylib.h"
#include "globals.h"

void UpdateSelectionHighlight(SelectionHighlight *highlight);
void StartSelectionBounce(SelectionHighlight *highlight);


void DrawCustomizationMenu(void);
void UpdateCustomizationMenu(void);
void ApplyTheme(int themeIndex);
Color GetRandomColor(void);


#endif // CUSTOM_H