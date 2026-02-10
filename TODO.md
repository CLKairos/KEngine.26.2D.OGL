# TODO
## Graphics module
- [] In Layer class, use another data type than vector in *Sprites* to make deletion faster.
- [] In spritesheet.cpp, cache UV coords so you don't have to calculate them every frame.
- [] Merge light system with rendering system
- [] Implement a better resource management
- [] Implement a better batch rendering system

## Text rendering
- [] Fix bug when rendering FPS with the number appearing first on the sstream
- [] Add linebreak in text rendering

## Error Catching
- [] Stop crashing everytime there is a slight issue|
- [] Create a change queue
- [] Use try{} error catching so that if an error occurs the entire program doesn't crash, the changes revert, and the error appears in the built in console.

## Conversion
- [x] Rename all Stella instances to KEngine