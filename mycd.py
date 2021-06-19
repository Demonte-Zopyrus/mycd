#!/usr/bin/env python3
import sys

# Author Yufei Pan

# The simulated command takes two path strings from the command line and prints either a new path or an error message.

# The first path is a current directory. The second path is a new directory.
# A directory name can only contain alphanumeric characters. A single dot (".") indicates a current directory, and
# the two consecutive dots ("..") indicate a step to a previous directory, up from the current one. A single forward slash "/" indicates a root directory.
# Multiple consecutive slashes are treated as equivalent to a single one.


# This will take in a string location and format it to output a valid address to the console
def printDir(dirName):
    # This removes all duplicated / s and construct a list from the input name
    dirList = list(filter(None, dirName.split('/')))
    newDirList = []
    if len(dirList) > 0:
        for dir in dirList:
            if dir == '.':
                # This means this directory, not adding anything
                continue
            elif dir == '..':
                # This means previous directory, going back if possible.
                if len(newDirList) > 0:
                    newDirList.pop()
            elif dir.isalnum():
                newDirList.append(dir)
            else:
                print(dir, ": No such file or directory")
                print('Note: directory name can only contain alphanumeric characters.')
    # print the new constructed list
    print('/' + '/'.join(newDirList))


def resolveDir(baseDir,cdPath):
    return baseDir + '/' + cdPath


if len(sys.argv) == 2:
    # One arguments had been passed in. Dereference it and print out the output directly
    printDir(sys.argv[1])
elif len(sys.argv) > 2:
    # At least two arguments had been passed in. We are only interested in the first two.
    targetDir = resolveDir(sys.argv[1],sys.argv[2])
    printDir(targetDir)
else:
    print('MyCD takes two arguments: ')
    print('The first path is a current directory. The second path is a new directory.')
    print('MyCD will decode and print out the final directory.')
    print('Note: directory name can only contain alphanumeric characters.')




