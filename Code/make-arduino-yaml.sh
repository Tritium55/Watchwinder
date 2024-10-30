# this is a command list your need to follow for using the arduino-cli

# create a new project
# arduino-cli sketch new test
# or: arduino-cli sketch {existing_directory}

# search for your board
arduino-cli board list

# generate the yaml file
# arduino-cli board attach -p /dev/ttyACM0 -b arduino:avr:uno test.ino
