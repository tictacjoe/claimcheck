# Claim Check — File Map (site repo)

This repo's own layout. For the full picture across both repos — including
the private working repo's trackers, entry directories, and scripts — see
`~/gjoe/debate-prep/docs/claimcheck-file-map.md`, the canonical file map.

## `~/gjoe/debate-prep-site/`

GitHub: `tictacjoe/claimcheck`

```
CLAUDE.md                    orientation for Claude Code
index.html                   the site itself
publish.py                   run from here, reads ../debate-prep
publish_exclude.txt          entries held back from publish

data/                        published JSON, read directly by index.html — not hand-edited
  prosecution.json
  deregulation.json
  government-services.json
  tracker.json               ~14MB — regenerated output, never Read in full

docs/                        site-specific content (separate from the private repo's docs/)
  claimcheck-methodology.md
  claimcheck-homepage-banner.md
  claimcheck-file-map.md     this file

tests/
  build-detail-html.test.js
test_publish.py
```

## Related repo

`tictacjoe/claimcheck-submissions` — separate public repo, no code, holds
claim suggestions as GitHub Issues. `index.html`'s "Suggest a Claim" link
points there. See the private repo's file map (link above) for its layout
and `~/gjoe/debate-prep/docs/claimcheck-submission-triage.md` for the
triage process.

## Live site

`https://tictacjoe.github.io/claimcheck/` — served directly from `data/*.json`
in this repo. No separate build step.

## Standing note

`publish.py` copies data from the private repo into `data/` but never commits
or pushes in either repo — check `git status` in both after any publish run.
