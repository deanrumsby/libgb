import init from '../build/gb.js';

const gb = await init();

const loadButton = document.querySelector('#load-button');

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

loadButton.addEventListener('change', onFileSelection);