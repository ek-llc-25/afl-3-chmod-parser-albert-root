#include "perms.h"

#include <stddef.h>

// TODO: Den her funktion virker kun for en utrolig begrænset mængde input (u-r)
//
// Den skulle også gerne virke for:
// - u, g, o
// - + og -
// - r, w, x, rw, rx, wx, rwx (eller en anden rækkefølge af dem)
bool chmod(const char *input, struct perms_t *perms) {
    if (input == NULL || perms == NULL) {
        return false;
    } else if (input[0] != 'u' && input[0] != 'g' && input[0] != 'o' && input[0] != 'a') {
        return false;
    } else if (input[1] != '+' && input[1] != '-') {
        return false;
    } else if (input[2] == '\0') {
        return false;
    }

    unsigned int perm_bits = 0;
    for (size_t i = 2; input[i] != '\0'; ++i) {
        switch (input[i]) {
            case 'r': perm_bits |= USER_READ;
                break;
            case 'w': perm_bits |= USER_WRITE;
                break;
            case 'x': perm_bits |= USER_EXECUTE;
                break;
            default: return false;
        }
    }

    switch (input[0]) {
        case 'u':
            break;
        case 'g':
            perm_bits >>= 3;
            break;
        case 'o':
            perm_bits >>= 6;
            break;
        case 'a':
            perm_bits = perm_bits | (perm_bits >> 3) | (perm_bits >> 6);
            break;
    }

    if (input[1] == '+') {
        perms->bits |= perm_bits;
    } else {
        perms->bits &= ~perm_bits;
    }

    return true;
}
