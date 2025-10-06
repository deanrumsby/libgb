const wasmPath = new URL('./gb.wasm', import.meta.url);

export default async function init() {
    const response = await fetch(wasmPath);
    const bytes = await response.arrayBuffer();
    const { instance: { exports } } = await WebAssembly.instantiate(bytes);

    console.log('exports', exports);

    return {}
}