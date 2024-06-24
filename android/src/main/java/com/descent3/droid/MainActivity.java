package com.descent3.droid;

import org.libsdl.app.SDLActivity;

public class MainActivity extends SDLActivity {
    @Override
    protected String[] getLibraries() {
        return new String[] {
            "SDL2",
            "Descent3",
        };
    }

    @Override
    protected String[] getArguments() {
        return super.getArguments();
    }
}
