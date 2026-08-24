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


def convert_report(markdown_text: str, working_dir: Path, site_dir: Path) -> str:
    """Apply the text transforms, then convert Markdown to an HTML
    fragment. Raw inline HTML (the <a id>/<sup> footnote markup) passes
    through the `markdown` library untouched by default -- confirmed
    empirically with markdown 3.10.3 -- which is what keeps the
    two-way footnote navigation working after conversion."""
    text = simplify_paths(markdown_text, working_dir, site_dir)
    text = rewrite_report_links(text)
    return markdown.markdown(text, extensions=["fenced_code"])


def extract_title_and_summary(markdown_text: str) -> tuple:
    """Pull the H1 title and a one-line description (the first real
    paragraph, skipping headings, blockquotes, and horizontal rules)
    out of a report's raw Markdown, for the index page listing."""
    lines = markdown_text.splitlines()

    title = ""
    for line in lines:
        if line.startswith("# "):
            title = line[2:].strip()
            break

    summary_lines = []
    in_summary = False
    for line in lines:
        stripped = line.strip()
        if not in_summary:
            if not stripped or stripped.startswith("#") or stripped.startswith(">") or stripped.startswith("---"):
                continue
            in_summary = True
        if not stripped:
            break
        summary_lines.append(stripped)

    summary = " ".join(summary_lines)
    return title, summary


def main():
    pass


if __name__ == "__main__":
    main()
