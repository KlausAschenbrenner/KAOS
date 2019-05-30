//
//  TextBox.c
//  KAOS
//
//  Created by Klaus Aschenbrenner on 16.05.2019.
//  Copyright (c) 2019 Klaus Aschenbrenner. All rights reserved.
//
//  This code is based on http://www.trackze.ro
//

#include "TextBox.h"
#include "../../drivers/keyboard.h"
#include "../../Heap/Heap.h"

// Creates a new TextBox
TextBox* NewTextBox(int X, int Y, int Width, int Height, Context *Context)
{
    TextBox *textbox = malloc(sizeof(TextBox));
    WindowInit((Window *)textbox, X, Y, Width, Height, WINDOW_NODECORATION, "", Context);
    textbox->Window.PaintFunction = TextBoxPaintHandler;
    textbox->Window.KeyPressFunction = TextBoxKeyPressHandler;
    textbox->Window.LeftMouseButtonUpFunction = TextBoxLeftMouseButtonUpHandler;
    textbox->HasFocus = 0;
    textbox->Pos = 0;

    return textbox;
}

// Draws the TextBox
void TextBoxPaintHandler(Window *TextBoxWindow, Rectangle *DirtyRegion)
{
    TextBox *textbox = (TextBox *)TextBoxWindow;
    int titleLen = strlen(textbox->Text) * 8;

    // White background
    ContextFillRect(TextBoxWindow->Context, 1, 1, TextBoxWindow->Width - 2, TextBoxWindow->Height - 2, 0xFFFF, DirtyRegion);

    if (textbox->HasFocus)
        ContextDrawRectangle(TextBoxWindow->Context, 0, 0, TextBoxWindow->Width, TextBoxWindow->Height, 0xF800, DirtyRegion);
    else
        ContextDrawRectangle(TextBoxWindow->Context, 0, 0, TextBoxWindow->Width, TextBoxWindow->Height, 0x0000, DirtyRegion);
    
    // Draw the title
    if (TextBoxWindow->Title)
        ContextDrawString(TextBoxWindow->Context, textbox->Text, 6, (TextBoxWindow->Height / 2) - 6, 0x0000, DirtyRegion);
}

// Handles the Left Mouse Button Up Event
void TextBoxLeftMouseButtonUpHandler(Window *TextBoxWindow, int X, int Y)
{
    TextBox *textbox = (TextBox *)TextBoxWindow;
    textbox->HasFocus = !textbox->HasFocus;

    if (textbox->HasFocus)
    {
        // The old, active TextBox has no focus anymore
        if (TextBoxWindow->Parent->ActiveTextBox != 0x0)
            TextBoxWindow->Parent->ActiveTextBox->HasFocus = 0;

        // And we finally set the new, active TextBox that has the focus now
        TextBoxWindow->Parent->ActiveTextBox = (Window *)TextBoxWindow;
    }
    else
    {
        TextBoxWindow->Parent->ActiveTextBox = 0x0;
    }
}

// Handles the Key Press Event
void TextBoxKeyPressHandler(Window *TextBoxWindow, char Key)
{
    TextBox *textbox = (TextBox *)TextBoxWindow;

    // Checks if the current TextBox is the current active TextBox on the Window
    if (textbox->HasFocus && TextBoxWindow->Parent->ActiveTextBox == TextBoxWindow)
    {
        // Checks if the current Window is the current active Window on the Desktop
        // TextBoxWindow->Parent->Parent: Reference to the Desktop
        // TextBoxWindow->Parent: Reference to the current Window
        if (TextBoxWindow->Parent->Parent->ActiveChild == TextBoxWindow->Parent)
        {
            // Currently we can only store up to 100 characters in a TextBox
            if (textbox->Pos < 100)
            {
                int processKey = 1;

                if (Key == KEY_BACKSPACE)
                {
                    processKey = 0;

                    // We only process the backspace key, if we have data already entered into the TextBox
                    if (textbox->Pos > 0)
                    {
                        // Clear out the last printed key
                        textbox->Pos--;
                        textbox->Text[textbox->Pos] = '\0';
                    }
                }

                if (processKey)
                {
                    Key = KeyboardKeyToASCII(Key, 0);

                    if (Key != 0)
                        textbox->Text[textbox->Pos++] = Key;
                }
            }
        }
    }
}