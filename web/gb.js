const wasmPath = new URL('./gb.wasm', import.meta.url);

export default async function init() {
    const response = await fetch(wasmPath);
    const bytes = await response.arrayBuffer();
    const { instance: { exports } } = await WebAssembly.instantiate(bytes);

    console.log('exports', exports);
    const gb = exports.gb_gameboy_create();

    return {
        b: () => exports.gb_registers_b_get(gb),
        c: () => exports.gb_registers_c_get(gb),
        load: (bytes) => {
            const maxRomSize = exports.gb_gameboy_rom_size_get();

            if (bytes.length > maxRomSize) {
                throw new Error(`ROM too big: Max ROM size is ${maxRomSize} bytes`);
            }

            const ptr = exports.gb_gameboy_rom_ptr_get(gb);
            console.log('ptr', ptr);
            const buffer = new Uint8Array(exports.memory.buffer);
            buffer.set(bytes, ptr);
        },
        step: () => exports.gb_gameboy_step(gb),
    }
}