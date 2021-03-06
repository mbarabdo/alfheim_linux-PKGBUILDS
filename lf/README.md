```
@dmarcoux/lf

AUR package for gokcehan/lf: A terminal file manager, heavily inspired by
ranger.
```

# Introduction

This repository is an
[AUR](https://wiki.archlinux.org/index.php/Arch_User_Repository) package for
[gokcehan/lf](https://github.com/gokcehan/lf).  For any information regarding
`lf` itself, please refer to its [repository](https://github.com/gokcehan/lf).
This AUR package is following GitHub releases of `lf`.  It doesn't follow every
commit on the `master` branch.

# Package Installation

Using your favorite [AUR
helper](https://wiki.archlinux.org/index.php/AUR_helpers), install the [lf
AUR package](https://aur.archlinux.org/packages/lf/) like this:

```bash
$ aura -A lf
```

# Package Maintenance

This section is mostly notes on how this package is maintained.

## Initial Setup

Whenever setting up the environment to maintain this package, these manual steps
must be done once.

### 1. Write Access to the AUR

Have a look on the
[wiki](https://wiki.archlinux.org/index.php/Arch_User_Repository#Authentication)
if you don't already have write access to the AUR.

### 2. Git Mirror

The `github.com/dmarcoux/lf` repository is a mirror of the
`aur.archlinux.org/lf` repository. Set it up by running the following
commands:

```bash
$ git clone git+ssh://aur@aur.archlinux.org/lf.git
$ git remote set-url origin --add git@github.com:dmarcoux/lf.git
```

## Routine Update

Whenever updating this package, these steps must always be done.

### 1. Generate the .SRCINFO file

The tool `mksrcinfo` provided by the [AUR package
`pkgbuild-introspection-git`](https://aur.archlinux.org/packages/pkgbuild-introspection-git)
is really useful to generate the `.SRCINFO` file. Simply run the command in the
repository's root directory to use it:

```bash
$ mksrcinfo
```

### 2. Generate the checksums in the PKGBUILD file

The script `updpkgsums` (which comes with `pacman`'s version 4.1 or greater) is
a simple way to generate the checksums in the `PKGBUILD` file. It is as simple
as running the script in the repository's root directory:

```bash
$ updpkgsums
```

### 3. Validate the PKGBUILD file

The script `makepkg` (which comes with `pacman`) is the usual way to validate a
`PKGBUILD` file. With a valid `PKGBUILD` file, it will create a package; with a
nonvalid `PKGBUILD` file, it will raise an error. Simply run the command in the
repository's root directory to use it:

```bash
$ makepkg
```

## Automation

All steps in the `Routine Update` section can be automated. To do so, I use a
git pre-commit hook ([pre-commit.sh](pre-commit.sh)).  Set it up by running the
following command in the repository's root directory:

```bash
$ ln -s ../../pre-commit.sh .git/hooks/pre-commit
```
