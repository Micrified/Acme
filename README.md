### Acme Tools

1. **div**: Generates a banner given a string on standard input.
2. **h2b**: Converts a hexadecimal string on stdin to a binary one on stdout.
3. **h2d**: Converts a hexadecimal string on stdin to a decimal one on stdout.
4. **linelint**: Parses program files and outputs any that exceed a set column limit.

### Usage

For the majority of these programs, I simply copy them into `/usr/local/bin` via:
	```gcc -o <name> <file>.c; sudo cp <name> /usr/local/bin```

The Acme editor can use these programs when they are typed into the tag bar. For example, if you are to write into the editor the word "My Functions", then highlight it and middle-click on a tag "|div", the input will be fed to the div program, which in turn will output a banner for the string. That banner will replace the highlighted text (the pipe prefix does this). There are many ways these programs can be used in Acme otherwise. I'm barely scratching the surface.

