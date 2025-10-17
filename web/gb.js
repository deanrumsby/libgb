const wasmPath = new URL('./gb.wasm', import.meta.url);

export default async function init() {
    const response = await fetch(wasmPath);
    const bytes = await response.arrayBuffer();
    const { instance: { exports } } = await WebAssembly.instantiate(bytes);

    console.log('exports', exports);
    const gb = exports.gb_gameboy_create();

    return {
        get pc() {
            return exports.gb_registers_pc_get(gb);
        },
        set pc(value) {
            exports.gb_registers_pc_set(gb, value);
        },
        get a() {
            return exports.gb_registers_a_get(gb);
        },
        set a(value) {
            exports.gb_registers_a_set(gb, value);
        },
        get b() {
            return exports.gb_registers_b_get(gb);
        },
        set b(value) {
            exports.gb_registers_b_set(gb, value);
        },
        get c() {
            return exports.gb_registers_c_get(gb);
        },
        set c(value) {
            exports.gb_registers_c_set(gb, value);
        },
        read: (address) => exports.gb_memory_get(gb, address),
        write: (address, value) => {
            exports.gb_memory_set(gb, address, value);
        },
        load: (bytes) => {
            const maxRomSize = exports.gb_gameboy_rom_size_get();

            if (bytes.length > maxRomSize) {
                throw new Error(`ROM too big: Max ROM size is ${maxRomSize} bytes`);
            }

            const ptr = exports.gb_gameboy_rom_ptr_get(gb);
            const buffer = new Uint8Array(exports.memory.buffer);
            buffer.set(bytes, ptr);
        },
        step: () => exports.gb_gameboy_step(gb),
        disassemble: () => {
            const disassembly = exports.gb_disassembly_create(gb);
            const ptr = exports.gb_disassembly_text_get(disassembly);
            const length = exports.gb_disassembly_length_get(disassembly);

            const utf8decoder = new TextDecoder();
            const encodedText = new Uint8Array(exports.memory.buffer, ptr, length);

            const decodedText = utf8decoder.decode(encodedText);
            exports.gb_disassembly_destroy(disassembly);

            return decodedText;
        }
    }
}