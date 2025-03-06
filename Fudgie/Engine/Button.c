//
//  Button.c
//  CSDL
//
//  Created by Erik Morris on 7/17/24.
//

#include "Button.h"
#include <SDL2/SDL_ttf.h>
#include <SDL3/SDL_events.h>

void Button_init(Button* button, float x, float y, float w, float h){
    button->buttonInfo.x = x;
    button->buttonInfo.y = y;
    button->buttonInfo.w = w;
    button->buttonInfo.h = h;
    //Texture_init(&button->buttonTextToDisplay);
    Texture_init(&button->buttonTexture);
}
void Button_initAndLoad(Button *button, SDL_Renderer *renderer, float x, float y, float w, float h, const char *buttonBackground, TTF_Font *gFont, const char *buttonText, SDL_Color textColor){
         button->buttonInfo.x = x;
    button->buttonInfo.y = y;
    button->buttonInfo.w = w;
    button->buttonInfo.h = h;
    button->text = (char*)buttonText;
    button->textColor = textColor;
    //Texture_init(&button->buttonTextToDisplay);
    Texture_init(&button->buttonTexture);
    if (!Texture_loadFromFile(&button->buttonTexture, renderer, buttonBackground))
    {
        printf("Failed to load buttonBackground!\n");
    }
    Texture_init_andLoadFromRenderedText(&button->buttonTextToDisplay, renderer, gFont, (SDL_FRect){x,y,w,h}, button->text, button->textColor);

}
void Button_free(Button* button){
    Texture_free(&button->buttonTexture);
    Texture_free(&button->buttonTextToDisplay);
}
void Button_setPosition(Button* button, float x, float y){
    button->buttonInfo.x=x;
    button->buttonInfo.y=y;
}
bool Button_loadTextures(Button* button, SDL_Renderer* renderer, const char* buttonBackground, const char* buttonText, TTF_Font *gFont, SDL_Color textColor){
    bool success = true;
    if (!Texture_loadFromFile(&button->buttonTexture, renderer, buttonBackground))
    {
        printf("Failed to load buttonBackground!\n");
        success = false;
    }
    button->text = (char*)buttonText;
    button->textColor = textColor;
    if (!Texture_loadFromRenderedText(&button->buttonTextToDisplay,renderer, gFont, buttonText, textColor))
    {
        printf("Failed to load buttonText!\n");
        success = false;
    }

    return success;
}
bool Button_loadTexturesDebug(Button* button, SDL_Renderer* renderer, const char* buttonBackground, const char* buttonText, SDL_Color textColor){
    bool success = true;
    if (!Texture_loadFromFile(&button->buttonTexture, renderer, buttonBackground))
    {
        printf("Failed to load buttonBackground!\n");
        success = false;
    }
    button->text = (char*)buttonText;
    button->textColor = textColor;
    // if (!Texture_loadFromRenderedText(&button->buttonTextToDisplay,renderer, gFont, buttonText, textColor))
    // {
    //     printf("Failed to load buttonText!\n");
    //     success = false;
    // }
     
    return success;
}
void Button_render(Button* button, SDL_Renderer* renderer){
    Texture_render(&button->buttonTexture, renderer, NULL, &button->buttonInfo, 0.0, NULL, SDL_FLIP_NONE);
    Texture_render(&button->buttonTextToDisplay, renderer, NULL, &button->buttonInfo, 0.0, NULL, SDL_FLIP_NONE);
    // SDL_SetRenderDrawColor(renderer, button->textColor.r, button->textColor.g, button->textColor.b, button->textColor.a);
    // SDL_RenderDebugText(renderer, button->buttonInfo.x, button->buttonInfo.y, button->text);
}
void Button_handleEvent(Button* button, SDL_Event* e){
    if (e->type == SDL_EVENT_MOUSE_MOTION || e->type == SDL_EVENT_MOUSE_BUTTON_DOWN ||
      e->type == SDL_EVENT_MOUSE_BUTTON_UP)
    {
        //Get mouse position
        float x, y;
        SDL_GetMouseState( &x, &y );
        //Check if mouse is in button
        bool inside = true;

        //Mouse is left of the button
        if( x < button->buttonInfo.x )
        {
            inside = false;
        }
        //Mouse is right of the button
        else if( x > button->buttonInfo.x + button->buttonInfo.w)
        {
            inside = false;
        }
        //Mouse above the button
        else if( y < button->buttonInfo.y )
        {
            inside = false;
        }
        //Mouse below the button
        else if( y > button->buttonInfo.y + button->buttonInfo.h)
        {
            inside = false;
        }
        //Mouse is outside button
        if( !inside )
        {
            Texture_setColor(&button->buttonTexture, 255, 255, 255);
        }
        //Mouse is inside button
        else
        {
            //Set mouse over sprite
            switch( e->type )
            {
                case SDL_EVENT_MOUSE_MOTION:
                    Texture_setColor(&button->buttonTexture, 200, 200, 200);
                break;
            
                case SDL_EVENT_MOUSE_BUTTON_DOWN:
                    Texture_setColor(&button->buttonTexture, 130, 130, 130);
                    button->isButtPressed = !button->isButtPressed;
                    // (button->isButtPressed) ? printf("Button true\n") : printf("Button false\n");
                break;
                
                case SDL_EVENT_MOUSE_BUTTON_UP:
                    Texture_setColor(&button->buttonTexture, 200, 200, 200);
                break;
            }
        }
    }
}
