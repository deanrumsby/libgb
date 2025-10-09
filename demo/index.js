import init from '../build/gb.js';

const gb = await init();

const loadButton = document.querySelector('#load-button');
const stepButton = document.querySelector('#step-button');

const bRegister = document.querySelector('#b-register');
const cRegister = document.querySelector('#c-register');

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
    bRegister.value = gb.b();
    cRegister.value = gb.c();
}

function onStep() {
    gb.step();
    updateRegisters();
}

loadButton.addEventListener('change', onFileSelection);
stepButton.addEventListener('click', onStep)

updateRegisters();