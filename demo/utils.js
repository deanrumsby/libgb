export const formatHex = (number, width, prefix = '') => `${prefix}${number.toString(16).toUpperCase().padStart(width, '0')}`;
export const formatDec = (number, width, prefix = '') => `${prefix}${number.toString(10).padStart(width, '0')}`;
