import init from '../build/gb.js';
import { formatHex, formatDec } from './utils.js';

const MEMORY_METADATA = {
    PAGE_SIZE: 256,
    PAGE_COUNT: 256
}

let memoryPage = 0;

const gb = await init();

const loadButton = document.querySelector('#load-button');
const stepButton = document.querySelector('#step-button');
const memoryPrevButton = document.querySelector('#memory-prev-button');
const memoryNextButton = document.querySelector('#memory-next-button');

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
    initMemoryView();
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

function initMemoryView() {
    const container = document.querySelector('#memory');
    container.replaceChildren(createMemoryPage(0));
    updateMemory();
}

function createMemoryPage(page) {
    if (page < 0 || page >= MEMORY_METADATA.PAGE_COUNT) return;

    const container = document.createElement('div');

    for (let i = 0; i < 16; i++) {
        const line = document.createElement('div');
        line.classList.add('memory-line');
        const offsetSpan = document.createElement('span');
        const lineOffset = page * MEMORY_METADATA.PAGE_SIZE + (i * 16);
        offsetSpan.textContent = formatHex(lineOffset, 4);

        const lineCells = document.createElement('div');
        for (let j = 0; j < 16; j++) {
            const input = document.createElement('input');
            input.classList.add('memory-cell');
            const offset = lineOffset + j;
            input.dataset.address = offset;
            lineCells.appendChild(input);
        }
        line.replaceChildren(offsetSpan, lineCells);
        container.appendChild(line);
    }

    return container;
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

function onMemoryPageNext() {
    const container = document.querySelector('#memory');
    const page = Math.min(memoryPage + 1, MEMORY_METADATA.PAGE_COUNT - 1);
    memoryPage = page;
    container.replaceChildren(createMemoryPage(page));
    updateMemory();
}

function onMemoryPagePrev() {
    const container = document.querySelector('#memory');
    const page = Math.max(memoryPage - 1, 0);
    memoryPage = page;
    container.replaceChildren(createMemoryPage(page));
    updateMemory();
}


function updateRegisters() {
    const container = document.querySelector('#registers');
    for (const register of registers) {
        const input = container.querySelector(`#${register.id}`);
        const value = register.get();
        input.value = register.format(value);
    }
}

function updateMemory() {
    const container = document.querySelector('#memory');
    const cells = container.querySelectorAll('.memory-cell');

    for (const cell of cells) {
        const value = gb.read(cell.dataset.address);
        cell.value = formatHex(value, 2);
    }
}

function onStep() {
    gb.step();
    updateRegisters();
}

loadButton.addEventListener('change', onFileSelection);
stepButton.addEventListener('click', onStep)
memoryNextButton.addEventListener('click', onMemoryPageNext);
memoryPrevButton.addEventListener('click', onMemoryPagePrev);

initUI();