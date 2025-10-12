import init from '../build/gb.js';
import { formatHex, formatDec } from './utils.js';

const gb = await init();

const loadButton = document.querySelector('#load-button');
const stepButton = document.querySelector('#step-button');

const registers = [
    {
        id: "b",
        label: "B:",
        bits: 8,
        format: (value) => formatHex(value, 2),
        get: () => gb.b,
    },
    {
        id: "c",
        label: "C:",
        bits: 8,
        format: (value) => formatHex(value, 2),
        get: () => gb.c,
    }
];

function initUI() {
    initRegistersView();
}

function initRegistersView() {
    const container = document.querySelector('#registers');

    for (const register of registers) {
        const div = document.createElement('div');
        div.classList.add('register');

        const input = document.createElement('input');
        input.id = register.id;
        input.dataset.bits = register.bits;

        const label = document.createElement('label');
        label.htmlFor = register.id;
        label.textContent = register.label;

        div.replaceChildren(label, input);
        container.appendChild(div);
    }

    updateRegisters();
}

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
    const container = document.querySelector('#registers');
    for (const register of registers) {
        const input = container.querySelector(`#${register.id}`);
        const value = register.get();
        input.value = register.format(value);
    }
}

function onStep() {
    gb.step();
    updateRegisters();
}

loadButton.addEventListener('change', onFileSelection);
stepButton.addEventListener('click', onStep)

initUI();