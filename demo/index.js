import init from '../build/gb.js';
import { formatHex, formatDec } from './utils.js';

///////////////////////////////////// constants ///////////////////////////////////////////////////

/**
 * The total count of addressable memory locations
 * 0x0000 to 0xffff;
 */
const MEMORY_TOTAL_SIZE = 0x10000;

/**
 * The number of memory addresses displayed per line in the memory viewer
 */
const MEMORY_PAGE_LINE_SIZE = 16;

/**
 * The number of lines shown on each page of the memory view.
 */
const MEMORY_PAGE_LINE_COUNT = 16;

/**
 * The number of memory locations shown on each page of the memory viewer.
 */
const MEMORY_PAGE_SIZE = MEMORY_PAGE_LINE_SIZE * MEMORY_PAGE_LINE_COUNT;

/**
 * The total number of pages viewable in the memory viewer.
 */
const MEMORY_PAGE_COUNT = MEMORY_TOTAL_SIZE / MEMORY_PAGE_SIZE;

/**
 * Config for the registers view. 
 * Used when sizing the input boxes and handling how to get and set values.
 */
const REGISTERS = [
    {
        id: "a",
        label: "A:",
        bits: 8,
        maxLength: 2,
        format: (value) => formatHex(value, 2),
        get: () => gb.a,
        set: (value) => {
            gb.a = value;
        }
    },
    {
        id: "b",
        label: "B:",
        bits: 8,
        maxLength: 2,
        format: (value) => formatHex(value, 2),
        get: () => gb.b,
        set: (value) => {
            gb.b = value;
        }
    },
    {
        id: "c",
        label: "C:",
        bits: 8,
        maxLength: 2,
        format: (value) => formatHex(value, 2),
        get: () => gb.c,
        set: (value) => {
            gb.c = value;
        }
    }
];

///////////////////////////////////// state ///////////////////////////////////////////////////////

/**
 * The WASM module.
 */
const gb = await init();

/**
 * The memory page currently displayed in the memory viewer.
 */
let currentMemoryPage = 0;

//////////////////////////////////// ui initializer functions /////////////////////////////////////

/**
 * Initializes the UI for the page.
 * Creating and fetching all initial data for the UI elements.
 */
function initUI() {
    initRegistersView();
    initMemoryView();
}

/**
 * Initializes the registers view. 
 * The registers view allows the user to inspect and edit all the values 
 * found in the registers of the Game Boy's SM83 CPU core.
 */
function initRegistersView() {
    const container = document.querySelector('#registers');

    for (const register of REGISTERS) {
        const div = document.createElement('div');
        div.classList.add('register');

        // set input attributes
        const input = document.createElement('input');
        input.id = register.id;
        input.dataset.bits = register.bits;
        input.maxLength = register.maxLength;

        // add listener that sets register values on edit
        input.addEventListener('input', (event) => {
            const valueAsString = event.target.value;
            const value = Number.parseInt(valueAsString, 16);

            if (Number.isInteger(value)) {
                register.set(value);
            }
        })

        const label = document.createElement('label');
        label.htmlFor = register.id;
        label.textContent = register.label;

        div.replaceChildren(label, input);
        container.appendChild(div);
    }

    updateRegisters();
}

/**
 * Initializes the memory view.
 * The memory view allows the user to inspect and edit all the memory addresses
 * that are connected on the bus. The range encompasses all 16-bit addresses i.e.
 * from 0x0000 to 0xffff.
 */
function initMemoryView() {
    viewMemoryPage(0);
}

//////////////////////////////////// update functions /////////////////////////////////////////////

/**
 * Updates all UI elements
 */
function updateUI() {
    updateRegisters();
    updateMemory();
}

/**
 * Updates the shown register values
 */
function updateRegisters() {
    const container = document.querySelector('#registers');
    for (const register of REGISTERS) {
        const input = container.querySelector(`#${register.id}`);
        const value = register.get();
        input.value = register.format(value);
    }
}

/**
 * Updates the shown memory values
 */
function updateMemory() {
    const container = document.querySelector('#memory');
    const cells = container.querySelectorAll('.memory-cell');

    for (const cell of cells) {
        const value = gb.read(cell.name);
        cell.value = formatHex(value, 2);
    }
}

//////////////////////////////////// helper functions /////////////////////////////////////////////

/**
 * Navigates to the memory page that contains the given address
 * and then applies highlighting to the exact cell.
 * @param {number} address 
 */
function viewMemoryAddress(address) {
    const container = document.querySelector('#memory');

    // view the page
    const page = Math.floor(address / MEMORY_PAGE_SIZE);
    viewMemoryPage(page);

    // apply highlighting
    const cell = container.querySelector(`input[name="${address}"]`);
    cell.classList.add('highlight');

    updateMemory();
}

/**
 * Updates the UI to show a particular page of memory.
 * @param {number} page the page index that should be viewed
 */
function viewMemoryPage(page) {
    const container = document.querySelector('#memory');
    container.replaceChildren(createMemoryPage(page));
    currentMemoryPage = page;
    updateMemory();
}

/**
 * Creates a 16 x 16 page of editable memory addresses.
 * @param {number} page the page index that should be created 
 * @returns {HTMLDivElement}
 */
function createMemoryPage(page) {
    const container = document.createElement('div');

    if (page < 0 || page >= MEMORY_PAGE_COUNT) {
        return container;
    }

    // create each line of 16 memory cells
    for (let i = 0; i < MEMORY_PAGE_LINE_COUNT; i++) {
        const offset = (MEMORY_PAGE_SIZE * page) + (i * MEMORY_PAGE_LINE_SIZE);
        const line = createMemoryLine(offset)
        container.appendChild(line);
    }

    return container;
}

/**
 * Creates a line of 16 memory addresses for use in the memory view.
 * @param {number} offset the starting address for the line
 * @returns {HTMLDivElement} the line
 */
function createMemoryLine(offset) {
    const container = document.createElement('div');
    container.classList.add('memory-line');

    // create the span that displays the offset for
    // this line
    const span = document.createElement('span');
    span.textContent = formatHex(offset, 4);

    // create the memory cells for the line
    const cells = document.createElement('div');

    for (let i = 0; i < MEMORY_PAGE_LINE_SIZE; i++) {
        const address = offset + i;

        // if the current address would be out of bounds then stop
        if (address < 0 || address >= MEMORY_TOTAL_SIZE) {
            break;
        }

        const input = document.createElement('input');
        input.classList.add('memory-cell');

        // set the address as the name so it
        // can be used by event listeners to edit 
        // and fetch the memory value
        input.name = address;

        // each cell can only hold two hexadecimal digits
        input.maxLength = 2;

        // attach a listener that writes to memory when editing
        input.addEventListener('input', (event) => {
            const valueAsString = event.target.value;
            const value = Number.parseInt(valueAsString, 16);

            if (Number.isInteger(value)) {
                gb.write(address, value);
            }
        });

        // append to the line
        cells.appendChild(input);
    }

    container.replaceChildren(span, cells);

    return container;
}

////////////////////////////////////// fixed ui ///////////////////////////////////////////////////

const loadButton = document.querySelector('#load-button');
const stepButton = document.querySelector('#step-button');
const memoryPrevButton = document.querySelector('#memory-prev-button');
const memoryNextButton = document.querySelector('#memory-next-button');
const memorySearchInput = document.querySelector('#memory-search');
const memoryRegionSelect = document.querySelector('#memory-select');

/////////////////////////////////////// handlers //////////////////////////////////////////////////

/**
 * Loads the ROM selected by the user into the Game Boy
 * @param {Event} event 
 */
async function onFileSelection(event) {
    const file = event.target.files[0];
    const buffer = await file.arrayBuffer();
    const bytes = new Uint8Array(buffer);
    gb.load(bytes);
    updateMemory();
}

/**
 * Handles when the user searches for a specific memory address
 * in the memory view.
 * @param {Event} event 
 */
function onMemorySearch(event) {
    const addressAsString = event.target.value;
    const address = Number.parseInt(addressAsString, 16);

    if (Number.isInteger(address)) {
        viewMemoryAddress(address);
    } else if (addressAsString === '') {
        viewMemoryPage(0);
    }
}

/**
 * Handles when a user selects a specific memory region
 * in the memory view.
 * @param {Event} event 
 */
function onMemoryRegionSelect(event) {
    const addressAsString = event.target.value;
    const address = Number.parseInt(addressAsString, 16);

    const page = Math.floor(address / MEMORY_PAGE_SIZE);
    viewMemoryPage(page);
}

/**
 * Handles when the user asks for the next page of memory
 * in the memory view.
 */
function onMemoryPageNext() {
    const page = Math.min(currentMemoryPage + 1, MEMORY_PAGE_COUNT - 1);
    viewMemoryPage(page);
    updateMemory();
}

/**
 * Handles when the user asks for the previous page of memory
 * in the memory view.
 */
function onMemoryPagePrev() {
    const page = Math.max(currentMemoryPage - 1, 0);
    viewMemoryPage(page);
    updateMemory();
}

/**
 * Handles when the user asks to proceed the emulation by one
 * machine cycle
 */
function onStep() {
    gb.step();
    updateUI();
}

///////////////////////////// event listeners /////////////////////////////////////////////////////

loadButton.addEventListener('change', onFileSelection);
stepButton.addEventListener('click', onStep)
memoryNextButton.addEventListener('click', onMemoryPageNext);
memoryPrevButton.addEventListener('click', onMemoryPagePrev);
memorySearchInput.addEventListener('input', onMemorySearch);
memoryRegionSelect.addEventListener('change', onMemoryRegionSelect);

////////////////////////////// start //////////////////////////////////////////////////////////////

initUI();