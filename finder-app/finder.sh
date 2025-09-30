#!/bin/sh
# Finder script for assignment 1
# Author: Aniruddh-D

# Check if correct number of arguments are provided
if [ $# -ne 2 ]; then
    echo "Error: Two arguments required."
    echo "Usage: $0 <filesdir> <searchstr>"
    echo "  filesdir: path to a directory on the filesystem"
    echo "  searchstr: text string to search within files"
    exit 1
fi

filesdir="$1"
searchstr="$2"

# Check if filesdir exists and is a directory
if [ ! -d "$filesdir" ]; then
    echo "Error: $filesdir does not represent a directory on the filesystem"
    exit 1
fi

# Count the number of files in the directory and all subdirectories
num_files=$(find "$filesdir" -type f | wc -l)

# Count the number of matching lines containing searchstr
num_matching_lines=$(find "$filesdir" -type f -exec grep -l "$searchstr" {} \; | xargs grep "$searchstr" | wc -l)

# Print the result
echo "The number of files are $num_files and the number of matching lines are $num_matching_lines"
