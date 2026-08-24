#!/usr/bin/env python3
"""
build_docs.py

Converts the Markdown reports in the PRIVATE working repo's
docs/reports/ (~/gjoe/tap-data/docs/reports/*.md, non-recursive --
never docs/reports/drafts/) into styled public HTML pages in the
PUBLIC site repo (~/gjoe/tap-site/reports/).

This does NOT commit or push anything -- it only writes files into the
site repo's working directory. You review with `git diff` in the site
repo and commit/push yourself, same discipline as publish.py.

The .md source files are only ever read, never modified.

Usage:
  python3 build_docs.py
  python3 build_docs.py --working ~/gjoe/tap-data --site ~/gjoe/tap-site
"""

import argparse
import re
import sys
from pathlib import Path

try:
    import markdown
except ImportError:
    print("ERROR: the 'markdown' package is required.")
    print("Install it with: pip install --break-system-packages markdown")
    sys.exit(1)


def simplify_paths(text: str, working_dir: Path, site_dir: Path) -> str:
    """Strip the private/public repo's absolute path prefixes so the
    generated public HTML doesn't expose local machine paths. Only runs
    on the in-memory copy being converted -- the .md source keeps its
    full absolute paths untouched."""
    text = text.replace(f"{working_dir}/", "")
    text = text.replace(f"{site_dir}/", "")
    text = text.replace(str(working_dir), "")
    text = text.replace(str(site_dir), "")
    return text


_MD_LINK_RE = re.compile(r"\]\(([^)]+?)\.md\)")


def rewrite_report_links(text: str) -> str:
    """Rewrite links to other reports (`](some-report.md)`) to point at
    the generated HTML file instead (`](some-report.html)`)."""
    return _MD_LINK_RE.sub(r"](\1.html)", text)


def main():
    pass


if __name__ == "__main__":
    main()
