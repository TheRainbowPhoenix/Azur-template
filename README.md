# Azur ClassPad Template

This is a small `gint` and Azur template for Hollyhock-3 on the ClassPad II.

It is set up for GitHub Codespaces. When the Codespace starts, it initializes the Azur submodule and installs the Azur third-party support files needed by CMake.

## Start in Codespaces

Open the repository in Codespaces and wait for the dev container setup to finish.

Then build the app:

```bash
fxsdk build-cp
```

The generated file is:

```text
AzurTemplate.hh3
```

Copy it to the root of your calculator storage next to `run.bin`, then launch it from Hollyhock Launcher.

## Start locally

If you are not using Codespaces, initialize the submodule and install Azur's third-party CMake files first:

```bash
git submodule update --init --recursive
bash scripts/setup-azur.sh
fxsdk build-cp
```

## Project layout

- `src/main.cxx` is the demo app.
- `azur` is the Azur submodule.
- `scripts/setup-azur.sh` prepares Azur's third-party files for the fxSDK toolchain.
- `.devcontainer` makes the project work in GitHub Codespaces.

## What the demo does

The app uses `azur_main_loop()` with one update function and one renderer function. It draws a color-changing triangle and prints Azur performance counters on screen.

Press `EXIT` to quit.

