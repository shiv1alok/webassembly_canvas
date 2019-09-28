# webassembly_canvas

## Introduction

Project to understand web assembly and how it works.
It explains both Exporting functions - Calling C from Javascript and Importing functions - Calling Javascript from C
canvas.c is having C code in it for generating dynamic circles
program.wasm is compiled web assembly code of canvas.c
canvas.js is utilizing program.wasm for calling C functions and exporting it's own functions for projecting animated circles on canvas

I have used vanilla js to create it. You can also use EMSCRIPTEN for wasm code, it will also give you a js file along with wasm.

Thanks

## Installation

1. npm install
2. npm start
3. Go to http://localhost:3333/

[check_demo](https://shiv1alok-webassembly-canvas.glitch.me)
