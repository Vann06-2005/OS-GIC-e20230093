# Lab 4 — Redirection and Pipelines: individual report

- Name / student ID: Phoung Sovannara / e20230093
- Linux account: gic-phoung-sovannara
- Personal status and other word: status = ok, other = done

## Commands I Used

My actual commands are saved one per line in `evidence/commands.txt`.

| Stage | My command | Input received | Output produced |
|---|---|---|---|
| Select exact first field | `grep '^ok,' data/events.csv \| tee evidence/selected.txt` | the 7 lines of `data/events.csv` (header + 6 records) | the 3 full rows `ok,7`, `ok,3`, `ok,7` (shown and saved) |
| Extract field 2 | `grep '^ok,' data/events.csv \| cut -d, -f2 \| tee evidence/fields.txt` | the 3 selected rows from `grep` | the 3 quantities `7`, `3`, `7` |
| Count selected records | `grep '^ok,' data/events.csv \| wc -l > evidence/normal.txt` | the 3 selected rows from `grep` | one number, `3` |
| Save stdout and stderr separately | `cat data/missing.csv > evidence/stdout.txt 2> evidence/stderr.txt` | a file name that does not exist | empty `stdout.txt`; `stderr.txt` holds `cat: data/missing.csv: No such file or directory` |
| Save exit status immediately | `echo $? > evidence/status.txt` | the exit status of the `cat` just before | `1` |

Between the stages, only the last command of the pipeline changed: first `grep` alone shows the full matching rows, then `cut` keeps only field 2 of those rows, then `wc -l` replaces the rows with the number of rows. `diff -u data/expected.txt evidence/normal.txt` printed nothing (status 0), so my count matches the expected count.

## What My Tests Show

| Test | Expected | Observed | Mistake it would catch |
|---|---|---|---|
| Original records | 3 exact matches | `3` (`ok-late,23` was not selected) | prefix matching: `grep '^ok'` without the comma would also select `ok-late` and give 4 |
| No match | 0 records | `0` (first line of `edge.txt`) | a pipeline that prints something even when no record matches |
| One added match plus a look-alike | 4 records | `4` (second line of `edge.txt`) | counting quantities instead of records (the new `ok,7` adds 1, not 7), prefix matching (`ok-late,99` must not count), and `>` instead of `>>` (the `0` from the first test would be lost) |
| Missing input | empty stdout, diagnostic on stderr, nonzero status | `stdout.txt` empty, `stderr.txt` has `No such file or directory`, status `1` | mixing errors into normal output, or thinking an empty result means success |

## Explain the Commands

1. **The comma in `grep '^ok,'`:** the comma ends the first field. `^ok` alone would also match `ok-late,23`, because that line also starts with `ok`. With the comma, only lines whose first field is exactly `ok` are selected.
2. **`wc -l` counts records:** `wc -l` counts lines, and after `grep` each line is one record. It never looks at the numbers inside. The sum of my quantities would be 7 + 3 + 7 = 17, which answers a different question than "how many records".
3. **Where I used `>>`:** for the second count in `evidence/edge.txt`. `>>` added `4` under the `0` from the no-match test. With `>`, the file would have been emptied first, and only `4` would be left.
4. **`tee` vs `>`:** `>` sends the output only into the file, so I see nothing on the screen. `tee` shows the output on the screen and saves the same output in the file, so I can check it while saving it.
5. **`echo $?` right after the command:** `$?` only holds the status of the last command that ran. If I run anything in between (even `cat evidence/stdout.txt`), `$?` is replaced by that command's status, usually 0, and I would save the wrong value.
6. **`cat missing-file | wc -l` can report 0:** a pipeline reports the status of its last command. `cat` fails and writes the error to stderr (which does not go through the pipe), but `wc -l` successfully counts 0 lines and exits with 0. So status 0 does not prove the input was read.

## Limits and Evidence

These commands assume simple comma-separated text without quoted commas. Saved results describe one run; they do not prove every future input works or who typed a command. `evidence/normal.txt` shows the number 3, but only `commands.txt` and the other evidence files show how I got it.
