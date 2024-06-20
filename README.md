![d3 (1)](https://github.com/DescentDevelopers/Descent3/assets/47716344/82ba0911-ee32-4565-84ee-b432c215ab95)

This is the Descent 3 open source engine, licensed under [GPL-3.0](https://github.com/DescentDevelopers/Descent3?tab=GPL-3.0-1-ov-file). It includes the '1.5' patch written by Kevin Bentley and Jeff Slutter several years ago and brought to a stable condition by the Descent community.

In order to use this, you must provide your own game files. See the **Usage** section for details.

## Version 1.5 Notes
There is no "release" yet. The current milestone is "1.5 Stable", which is meant to more or less be Descent 3 as it might have been if the 1.5 patch had made it to retail years ago. Artifacts can be downloaded from the [Actions](https://github.com/DescentDevelopers/Descent3/actions) tab.
The milestone needs testing on all platforms. Please report issues when found.

## Usage
1. Make sure that you have a copy of Descent 3. You can purchase a copy of Descent 3 from [GOG](https://www.gog.com/game/descent_3_expansion) or [Steam](https://store.steampowered.com/app/273590/Descent_3/).
2. Install Descent 3.

    - **Note for Steam users:** If you own Descent 3 on Steam, then it’s recommended that you install the Windows version of the game even if you’re running macOS or Linux, otherwise movies will not work due to [current lack of Ogv support](https://github.com/DescentDevelopers/Descent3/issues/240). You can use either [Steam Play](https://help.steampowered.com/en/faqs/view/08F7-5D56-9654-39AF) or [SteamCMD](https://developer.valvesoftware.com/wiki/SteamCMD#Cross-Platform_Installation) to install the Windows version of the game on macOS or Linux.

    - **Note for non-Windows users:** If you have the Windows version of the game on CDs but you don’t want to use Windows to install them, then you can follow these instructions:

        <details>
        <summary>How to install the Windows Dual-Jewel version of Descent 3 in Wine</summary>

        <ol type="1">
            <li>Make sure that you have <a href="https://www.winehq.org">Wine</a> installed.</li>
            <li><i>(Recommended)</i> Run <code>winecfg</code> and make sure that “Emulate a virtual desktop” is enabled.</li>
            <li>
                <p><i>(Optional)</i> Determine if you’re going to be affected by a bug with Descent 3’s installer, and potentially apply a workaround:</p>
                <ol type="a">
                    <li>Download <a href="https://codeberg.org/JasonYundt/environment-size-checker">Environment Size Checker</a>.</li>
                    <li>Run <code>wine environment-size-checker.exe</code>.</li>
                    <li>If that program tells you that your environment is more than 32,724 bytes large, then you’ll need to unset or shorten environment variables before running Descent 3’s installer. If you don’t, then the installer will page fault.</li>
                </ol>
            </li>
            <li>
                <p>Install Descent 3:</p>
                <ol type="a">
                    <li>Insert disc 1.</li>
                    <li>Make sure that disc 1 is mounted.</li>
                    <li>Determine which drive letter Wine is using for your CD drive. (Hint: try running <code>wine explorer</code>).</li>
                    <li>Run <code>wine '&lt;drive-letter&gt;:\Setup.exe'</code>.</li>
                    <li>Follow the installation wizard’s instructions until it asks you to choose a “Setup Type”.</li>
                    <li>Select the “Full” Setup Type, then click “Next”.
                    <li>Continue following the installation wizard’s instructions until it asks you to insert disc 2.</li>
                    <li>
                        <p>Switch to disc 2:</p>
                        <!-- This really should be an <ol>, but I couldn’t get the numbering/lettering to work right: <https://github.com/orgs/community/discussions/124850> -->
                        <ul>
                            <li>Run <code>wine eject &lt;drive-letter&gt;:</code>.</li>
                            <li>Make sure that the disc was unmounted and ejected.</li>
                            <li>Insert disc 2.</li>
                            <li>Mount disc 2.</li>
                        </ul>
                    </li>
                    <li>Continue following the installation wizard’s instructions until it asks you to insert disc 1 again.</li>
                    <li>Switch back to disc 1. Follow a similar procedure to the one that you used to switch to disc 2.</li>
                    <li>Finish the going through the installation wizard.</li>
                    <li>When the installation wizard finishes, it will open an explorer window. Close out of that window.</li>
                    <li>Unmount the disc.</li>
                    <li>Eject the disc.</li>
                </ol>
            <li>
                <p>Install Descent 3: Mercenary:</p>
                <ol type="a">
                    <li>Insert disc 3.</li>
                    <li>Make sure that disc 3 is mounted.</li>
                    <li>Run <code>wine start /d &lt;drive-letter&gt;: setup.exe -autorun</code>.</li>
                    <li>Follow the instructions in the installation wizard.</li>
                </ol>
            </li>
        </ol>

        </details>

3. If your version of Descent 3 is older than v1.4, then [update it to v1.4](http://descent3.com/downloads.php).
4. Create a new folder named `D3-open-source`.
5. Copy the following files from your installation of Descent 3 to `D3-open-source`:
    - All `.hog` files
    - The `missions` folder
    - _(Optional)_ All `.pld` files
    - _(Optional)_ The `demo` folder
    - _(Optional)_ The `movies` folder
6. Create the following folders in `D3-open-source`:
    - `custom/`
    - `custom/cache/`
7. Obtain new Descent 3 engine files:
    - If you want to use pre-built binaries, then download one of the artifacts from our latest CI run. You can find a list of CI runs [here](https://github.com/DescentDevelopers/Descent3/actions/workflows/build.yml?query=branch%3Amain).
    - If you want to build the engine files yourself, the follow [these instructions](#building). Once you build the engine files, they’ll be put in `builds/<platform>/Descent3/<build-type>/`. For example, if you’re using Linux and you create a “Release” build, then the files will be located at `builds/linux/Descent3/Release`.
8. Copy all of the new engine files into `D3-open-source` and overwrite any conflicts.
9. Run the game:
    - On Windows, run `D3-open-source\Descent3.exe`.
    - On other platforms, run `D3-open-source/Descent3`.
10. Special notes:
    - D3 Open Source compiles level scripts in their own hogfiles. Make sure you copy and overwrite `d3-{platform}.hog`.

## Building
#### Building - Windows
1. Make sure that you have Git and Visual Studio 2022 with the “Desktop development with C++” workload. If you don’t already have those installed or you aren’t sure, then open an elevated Command Prompt and run:

    <!--
    The following code block specifies the full path to the Visual Studio Installer because the Visual Studio Installer doesn’t add itself to the user’s Path. The installer is guaranteed to be in a specific location on 64-bit systems [1]. The installer will be in a different location on 32-bit systems [2], but Visual Studio 2022 doesn’t support 32-bit systems [3] so we can ignore that detail.

    [1]: <https://learn.microsoft.com/en-us/visualstudio/install/use-command-line-parameters-to-install-visual-studio?view=vs-2022>
    [2]: <https://github.com/microsoft/vswhere/wiki#installing>
    [3]: <https://learn.microsoft.com/en-us/answers/questions/1689898/does-visual-studio-build-tools-2022-support-32-bit>
    -->

    ```batch
    winget install Git.Git Microsoft.VisualStudio.2022.Community

    "%ProgramFiles(x86)%\Microsoft Visual Studio\Installer\setup.exe" modify^
        --passive^
        --channelId VisualStudio.17.Release^
        --productId Microsoft.VisualStudio.Product.Community^
        --add Microsoft.VisualStudio.Workload.NativeDesktop;includeRecommended
    ```

2. Open a “x86 Native Tools Command Prompt” and run:

    ```batch
    git clone https://github.com/DescentDevelopers/Descent3
    cd Descent3
    cmake --preset win32 -D ENABLE_LOGGER=[ON|OFF]
    cmake --build --preset win32 --config [Debug|Release]
    ```

Once CMake finishes, the built files will be put in `builds\win32\Descent3\Debug` or `builds\win32\Descent3\Release`.

#### Building - macOS
1. Make sure that [Xcode](https://developer.apple.com/xcode) is installed.

2. Make sure that [Homebrew](https://brew.sh) is installed.

3. Run these commands:

    ```sh
    git clone https://github.com/DescentDevelopers/Descent3
    cd Descent3
    brew bundle install
    cmake --preset mac -D ENABLE_LOGGER=[ON|OFF]
    cmake --build --preset mac --config [Debug|Release]
    ```

Once CMake finishes, the built files will be put in `builds/mac/Descent3/Debug` or `builds/mac/Descent3/Release`.

#### Building - Linux (Ubuntu)
Run these commands:

```sh
sudo apt update
sudo apt install -y --no-install-recommends git ninja-build cmake g++ libsdl2-dev zlib1g-dev
git clone https://github.com/DescentDevelopers/Descent3
cd Descent3
cmake --preset linux -D ENABLE_LOGGER=[ON|OFF]
cmake --build --preset linux --config [Debug|Release]
```

Once CMake finishes, the built files will be put in `builds/linux/Descent3/Debug` or `builds/linux/Descent3/Release`.

#### Building - Linux (Fedora)
Run these commands:

```sh
sudo dnf update --refresh
sudo dnf install -y git ninja-build cmake gcc-c++ SDL2-devel zlib-devel
git clone https://github.com/DescentDevelopers/Descent3
cd Descent3
cmake --preset linux -D ENABLE_LOGGER=[ON|OFF]
cmake --build --preset linux --config [Debug|Release]
```

Once CMake finishes, the built files will be put in `builds/linux/Descent3/Debug` or `builds/linux/Descent3/Release`.

## Contributing
Anyone can contribute! We have an active Discord presence at [Descent Developer Network](https://discord.gg/GNy5CUQ). If you are interested in maintaining the project on a regular basis, please contact Kevin Bentley.
