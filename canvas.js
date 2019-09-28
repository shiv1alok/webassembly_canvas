console.log('Canvas js loaded');
const canvas = document.getElementById('canvas');
canvas.width = screen.width;
canvas.height = screen.height;
const context = canvas.getContext('2d');

const randomNumber = (max) => {
    let randNum = Math.floor(Math.random() * (max - 1 + 1) + 1);
    return randNum;
};

// Render circles on canvas
const render = (dataLength, singleCircleSize) => {
    // Assigning C getCircles function to getCirc | Get circles data from WASM (C)
    const getCirc = window.wasm.instance.exports.getCircles;
    // Get WebAssembly Module wasmMemory
    const waMemoryBuffer = window.wasm.instance.exports.memory.buffer;
    let circles = new Int32Array(waMemoryBuffer, getCirc(canvas.width, canvas.height), dataLength);

    // Clear canvas to re render
    context.clearRect(0, 0, canvas.width, canvas.height);

    for (let i = 0; i < circles.length; i += singleCircleSize) {
        // Get the circle chunks
        let circle = circles.slice(i, i + singleCircleSize);

        // Draw circle
        context.beginPath();
        context.arc(circle[0], circle[1], circle[2], 0, 2 * Math.PI, false);
        context.fillStyle = `rgba(${circle[3]},${circle[4]},${circle[5]},1)`;
        context.fill();
    }

    // Request next animation frame with updated circles (re-render)
    reRenderCircles(dataLength, singleCircleSize);
};

const imports = {
    env: {
        renderCanvas: render,
        generateRandom: randomNumber
    }
};

WebAssembly.instantiateStreaming(fetch('/program.wasm'), imports)
    .then((wasm) => {
        window.wasm = wasm;
        wasm.instance.exports.main();
    });

const reRenderCircles = (dataLength, singleCircleSize) => {
    // Request next animation frame and re-render with updated circles
    window.requestAnimationFrame(() => {
        render(dataLength, singleCircleSize)
    });
};