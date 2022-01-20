/*
Copyright (c) 2012-2022 Oscar Riveros (@maxtuno, Chile).

Permission is hereby granted, free of charge, to any person obtaining
a copy of this software and associated documentation files (the
"Software"), to deal in the Software without restriction, including
without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and/or sell copies of the Software, and to
permit persons to whom the Software is furnished to do so, subject to
the following conditions:

The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include <hess/hess.hh>

std::map<std::size_t, bool> db;

#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define MAX(a, b) (((a) > (b)) ? (a) : (b))

void hashing(struct cpu *box) {
    box->key = 0;
    for (box->k = 0; box->k < box->len; box->k++) {
        box->key ^= box->seq[box->k] + 0x9e3779b9 + (box->key << 6) + (box->key >> 2);
    }
}

void inv(struct cpu *box) {
    box->m = MIN(box->i, box->j);
    box->n = MAX(box->i, box->j);
    while (box->i < box->j) {
        box->cmp++;
        box->ram = box->seq[box->i];
        box->seq[box->i] = box->seq[box->j];
        box->seq[box->j] = box->ram;
        box->i++;
        box->j--;
    }
    box->i = box->m;
    box->j = box->n;
}

bool next_orbit(struct cpu *box) {
    for (box->i = 0; box->i < box->len; box->i++) {
        for (box->j = box->i; box->j < box->len; box->j++) {
            hashing(box);
            if (!db[box->key]) {
                db[box->key] = true;
                goto finally;
            } else {
                inv(box);
            }
        }
    }
    return false;
    finally:
    return true;
}

void hess(struct cpu *box) {
    I cur = INT32_MAX;
    box->sat = false;
    while (next_orbit(box)) {
        box->glb = INT32_MAX;
        for (box->i = 0; box->i < box->len; box->i++) {
            for (box->j = 0; box->j < box->len; box->j++) {
                // this trick only for HP
                if (box->map[box->seq[!box->i ? box->len - 1 : box->i - 1]][box->seq[box->i]] + box->map[box->seq[!box->j ? box->len - 1 : box->j - 1]][box->seq[box->j]] <= 1) {
                    inv(box);
                    box->loc = 0;
                    for (box->k = 0; box->k < box->len - 1; box->k++) {
                        box->cmp++;
                        box->loc += !box->map[box->seq[box->k]][box->seq[box->k + 1]];
                        if (box->loc > box->glb) {
                            break;
                        }
                    }
                    if (box->loc < box->glb) {
                        box->glb = box->loc;
                        if (box->glb < cur) {
                            cur = box->glb;
                            box->sat = !box->glb;
                            if (box->log) {
                                box->log(box);
                            }
                            if (box->sat) {
                                return;
                            }
                        }
                    } else if (box->loc > box->glb) {
                        inv(box);
                    }
                }
            }
        }
    }
}
