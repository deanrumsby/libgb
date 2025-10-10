import init from '../build/gb.js';
import { formatHex, formatDec } from './utils.js';

const gb = await init();

const loadButton = document.querySelector('#load-button');
const stepButton = document.querySelector('#step-button');

const registerB = document.querySelector('#register-b');
const registerC = document.querySelector('#register-c');

/**
 * Loads the ROM selected by the user into the Game Boy
 * @param {Event} event 
 */
async function onFileSelection(event) {
    const file = event.target.files[0];
    const buffer = await file.arrayBuffer();
    const bytes = new Uint8Array(buffer);
    gb.load(bytes);
}


function updateRegisters() {
    registerB.value = formatHex(gb.b(), 2);
    registerC.value = formatHex(gb.c(), 2);
}

function onStep() {
    gb.step();
    updateRegisters();
}

loadButton.addEventListener('change', onFileSelection);
stepButton.addEventListener('click', onStep)

updateRegisters();