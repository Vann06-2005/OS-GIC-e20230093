# Lab 3 — Wildcards, Hard Links and Symbolic Links: individual report

- Student name/ID: Phoung Sovannara / e20230093
- Ubuntu username: gic-phoung-sovannara
- My values (`oslab values lab3`): name = silver, tag = final, v1 = 200, v2 = 284
- Files: `evidence/wildcards.txt`, `evidence/links.txt`, `evidence/replacement.txt`, `evidence/checkpoint.txt`

## What I Saw

| State | What `cat` printed for the hard link | What `cat` printed for the symbolic link | What `readlink` printed |
|---|---|---|---|
| Before the rename | `version 200` | `version 200` | `silver.txt` |
| After the rename, before the repair | `version 200` | `cat: silver-soft.txt: No such file or directory` | `silver.txt` |
| After a new file took the old name | `version 200` | `version 284` | `silver.txt` |
| After my repair | `version 200` | `version 200` | `silver-final.txt` |

My repair (the two commands I wrote), run inside `links/`:

```bash
rm -- "$name-soft.txt"
ln -s "$name-$tag.txt" "$name-soft.txt"
```

The target is only `silver-final.txt` because a relative target is read from the folder that holds the link, and the report is in the same folder (`links/`).

## Explanation

My original report has inode 19142462, and `silver-hard.txt` has the same inode, so they are one file with two names. When I renamed `silver.txt` to `silver-final.txt`, the inode did not change, so the hard link still read `version 200`. The symbolic link only stores the text `silver.txt`, so after the rename no file had that name and the link was dangling. The new `silver.txt` got a different inode, 19146293, and holds `version 284`; the symbolic link found that name again and read the new file. The surprise for me was the symbolic link: it worked again without any error, but it read the wrong file.

## What My Tests Do Not Prove

`cat` only shows the content, so two names that print `version 200` could still be two separate copies; only the same inode number in `ls -li` proves that `silver-hard.txt` and `silver-final.txt` are the same file. A symbolic link that `cat` can read also does not prove it points to the right file, as the new `silver.txt` showed.
