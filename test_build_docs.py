from pathlib import Path

from build_docs import simplify_paths, rewrite_report_links


def test_simplify_paths_strips_working_repo_prefix():
    working = Path("/tmp/example/tap-data")
    site = Path("/tmp/example/tap-site")
    text = f"Command: `python3 {working}/prosecution/find_stale_prosecution_entries.py`"

    result = simplify_paths(text, working, site)

    assert result == "Command: `python3 prosecution/find_stale_prosecution_entries.py`"


def test_simplify_paths_strips_site_repo_prefix():
    working = Path("/tmp/example/tap-data")
    site = Path("/tmp/example/tap-site")
    text = f"Location: `{site}/data/community-topics.json`"

    result = simplify_paths(text, working, site)

    assert result == "Location: `data/community-topics.json`"


def test_simplify_paths_leaves_unrelated_text_untouched():
    working = Path("/tmp/example/tap-data")
    site = Path("/tmp/example/tap-site")
    text = "This sentence has no local paths in it at all."

    result = simplify_paths(text, working, site)

    assert result == text


def test_simplify_paths_strips_bare_working_dir_path():
    working = Path("/tmp/example/tap-data")
    site = Path("/tmp/example/tap-site")
    text = f"Location: `{working}`"

    result = simplify_paths(text, working, site)

    assert result == "Location: ``"


def test_simplify_paths_strips_bare_site_dir_path():
    working = Path("/tmp/example/tap-data")
    site = Path("/tmp/example/tap-site")
    text = f"Location: `{site}`"

    result = simplify_paths(text, working, site)

    assert result == "Location: ``"


def test_rewrite_report_links_converts_md_to_html():
    text = "See [the guide](./tap-sweep-cabinet-legal-exposure.md) for details."

    result = rewrite_report_links(text)

    assert result == "See [the guide](./tap-sweep-cabinet-legal-exposure.html) for details."


def test_rewrite_report_links_handles_multiple_links_in_one_line():
    text = (
        "See [Ingestion Pipeline](./tap-sweep-reporting-database-updates.md) or "
        "[Backlog Triage](./tap-sweep-reporting-backlog-triage.md)."
    )

    result = rewrite_report_links(text)

    assert "](./tap-sweep-reporting-database-updates.html)" in result
    assert "](./tap-sweep-reporting-backlog-triage.html)" in result


from build_docs import convert_report


def test_convert_report_preserves_footnote_anchor_and_return_link():
    working = Path("/tmp/example/tap-data")
    site = Path("/tmp/example/tap-site")
    text = (
        "The sweep begins with an automated scanning script."
        '<a id="ref-scanning-script"></a><sup>[tn](#scanning-script)</sup>\n\n'
        "## Technical Appendix\n\n"
        "### Scanning Script\n"
        f"Command: `python3 {working}/prosecution/find_stale_prosecution_entries.py`  \n"
        "[↩ Return to text](#ref-scanning-script)\n"
    )

    html = convert_report(text, working, site)

    assert '<a id="ref-scanning-script"></a>' in html
    assert '<a href="#scanning-script">tn</a>' in html
    assert '<a href="#ref-scanning-script">↩ Return to text</a>' in html


def test_convert_report_strips_absolute_paths_in_code_spans():
    working = Path("/tmp/example/tap-data")
    site = Path("/tmp/example/tap-site")
    text = f"Location: `{working}/prosecution/cabinet-level/`"

    html = convert_report(text, working, site)

    assert str(working) not in html
    assert "<code>prosecution/cabinet-level/</code>" in html


def test_convert_report_rewrites_report_links():
    working = Path("/tmp/example/tap-data")
    site = Path("/tmp/example/tap-site")
    text = "See [the guide](./tap-sweep-cabinet-legal-exposure.md) for details."

    html = convert_report(text, working, site)

    assert '<a href="./tap-sweep-cabinet-legal-exposure.html">' in html
    assert ".md" not in html


def test_convert_report_renders_fenced_code_blocks():
    working = Path("/tmp/example/tap-data")
    site = Path("/tmp/example/tap-site")
    text = "```markdown\nThe sweep begins.<sup>[tn](#slug)</sup>\n```\n"

    html = convert_report(text, working, site)

    assert "<pre>" in html
    assert "<code" in html


from build_docs import extract_title_and_summary


def test_extract_title_and_summary_skips_blockquote_before_first_heading():
    text = (
        "# The Accountability Project — Overview\n\n"
        '> "While headlines flood, the record stands."\n\n'
        "## Introduction\n\n"
        "The Accountability Project began in early 2025 as a personal "
        "reference archive of news reports.\n\n"
        "More text in a later paragraph that should not be included.\n"
    )

    title, summary = extract_title_and_summary(text)

    assert title == "The Accountability Project — Overview"
    assert summary == (
        "The Accountability Project began in early 2025 as a personal "
        "reference archive of news reports."
    )


def test_extract_title_and_summary_skips_straight_to_heading_and_paragraph():
    text = (
        "# The Accountability Project — Cabinet-Level Legal Exposure "
        "Update Sweeps\n\n"
        "## Concept & Purpose\n"
        "A Cabinet-Level Legal Exposure Update Sweep is a systematic, "
        "multi-stage audit and verification pipeline.\n"
    )

    title, summary = extract_title_and_summary(text)

    assert title == (
        "The Accountability Project — Cabinet-Level Legal Exposure "
        "Update Sweeps"
    )
    assert summary == (
        "A Cabinet-Level Legal Exposure Update Sweep is a systematic, "
        "multi-stage audit and verification pipeline."
    )
