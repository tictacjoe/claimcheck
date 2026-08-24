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


from build_docs import render_page, render_index


def test_render_page_includes_title_body_and_back_links():
    html = render_page(
        "Cabinet-Level Legal Exposure",
        "<p>Body content here.</p>",
        back_links=[("All Reports", "index.html"), ("Back to The Accountability Project", "../index.html")],
    )

    assert "<title>Cabinet-Level Legal Exposure — The Accountability Project</title>" in html
    assert "<h1>Cabinet-Level Legal Exposure</h1>" in html
    assert "<p>Body content here.</p>" in html
    assert '<a class="back-link" href="index.html">&larr; All Reports</a>' in html
    assert '<a class="back-link" href="../index.html">&larr; Back to The Accountability Project</a>' in html


def test_render_index_lists_reports_with_overview_first():
    reports = [
        {"slug": "tap-sweep-corporate-deregulation", "title": "Corporate Deregulation", "summary": "Tracks rollbacks."},
        {"slug": "tap-project-overview", "title": "Overview", "summary": "The project overview."},
        {"slug": "tap-sweep-cabinet-legal-exposure", "title": "Cabinet-Level Legal Exposure", "summary": "Tracks liability."},
    ]

    html = render_index(reports)

    overview_pos = html.index("tap-project-overview.html")
    cabinet_pos = html.index("tap-sweep-cabinet-legal-exposure.html")
    dereg_pos = html.index("tap-sweep-corporate-deregulation.html")
    assert overview_pos < cabinet_pos < dereg_pos
    assert "<p>The project overview.</p>" in html


from build_docs import build_docs


def test_build_docs_writes_one_html_file_per_report_and_an_index(tmp_path):
    working = tmp_path / "tap-data"
    site = tmp_path / "tap-site"
    reports_dir = working / "docs" / "reports"
    reports_dir.mkdir(parents=True)

    (reports_dir / "tap-project-overview.md").write_text(
        "# The Accountability Project — Overview\n\n"
        "## Introduction\n\n"
        "The Accountability Project began in early 2025.\n"
    )
    (reports_dir / "tap-sweep-cabinet-legal-exposure.md").write_text(
        "# The Accountability Project — Cabinet-Level Legal Exposure "
        "Update Sweeps\n\n"
        "## Concept & Purpose\n"
        "A Cabinet-Level Legal Exposure Update Sweep tracks statutory "
        "liability.\n"
    )

    build_docs(working, site)

    overview_html = (site / "reports" / "tap-project-overview.html").read_text()
    assert "<h1>The Accountability Project — Overview</h1>" in overview_html
    assert "The Accountability Project began in early 2025." in overview_html

    cabinet_html = (site / "reports" / "tap-sweep-cabinet-legal-exposure.html").read_text()
    assert "Cabinet-Level Legal Exposure Update Sweeps" in cabinet_html

    index_html = (site / "reports" / "index.html").read_text()
    assert "tap-project-overview.html" in index_html
    assert "tap-sweep-cabinet-legal-exposure.html" in index_html


def test_build_docs_ignores_drafts_subfolder(tmp_path):
    working = tmp_path / "tap-data"
    site = tmp_path / "tap-site"
    reports_dir = working / "docs" / "reports"
    drafts_dir = reports_dir / "drafts"
    drafts_dir.mkdir(parents=True)

    (reports_dir / "tap-project-overview.md").write_text(
        "# Overview\n\nReal content.\n"
    )
    (drafts_dir / "tap-project-overview-v1.md").write_text(
        "# Old Draft\n\nSuperseded content.\n"
    )

    build_docs(working, site)

    assert (site / "reports" / "tap-project-overview.html").exists()
    assert not (site / "reports" / "tap-project-overview-v1.html").exists()


def test_build_docs_excludes_video_narration_script(tmp_path):
    working = tmp_path / "tap-data"
    site = tmp_path / "tap-site"
    reports_dir = working / "docs" / "reports"
    reports_dir.mkdir(parents=True)

    (reports_dir / "tap-project-overview.md").write_text(
        "# Overview\n\nReal content.\n"
    )
    (reports_dir / "video_narration_script.md").write_text(
        "# TAP Video Presentation — Narration Scripts\n\n"
        "## Slide 1\nWelcome to The Accountability Project.\n"
    )

    build_docs(working, site)

    assert (site / "reports" / "tap-project-overview.html").exists()
    assert not (site / "reports" / "video_narration_script.html").exists()
    index_html = (site / "reports" / "index.html").read_text()
    assert "video_narration_script" not in index_html


def test_build_docs_excludes_tap_docs_audit_and_publishing_report(tmp_path):
    working = tmp_path / "tap-data"
    site = tmp_path / "tap-site"
    reports_dir = working / "docs" / "reports"
    reports_dir.mkdir(parents=True)

    (reports_dir / "tap-project-overview.md").write_text(
        "# Overview\n\nReal content.\n"
    )
    (reports_dir / "tap-docs-audit-and-publishing-report.md").write_text(
        "# Internal Audit and Publishing Report\n\n"
        "## Engineering Session\nPrivate project-management narrative and git references.\n"
    )

    build_docs(working, site)

    assert (site / "reports" / "tap-project-overview.html").exists()
    assert not (site / "reports" / "tap-docs-audit-and-publishing-report.html").exists()
    index_html = (site / "reports" / "index.html").read_text()
    assert "tap-docs-audit-and-publishing-report" not in index_html


def test_build_docs_skips_unreadable_file_and_continues(tmp_path, capsys):
    working = tmp_path / "tap-data"
    site = tmp_path / "tap-site"
    reports_dir = working / "docs" / "reports"
    reports_dir.mkdir(parents=True)

    (reports_dir / "tap-project-overview.md").write_text(
        "# Overview\n\nGood content that should still convert.\n"
    )
    # Invalid UTF-8 bytes -- read_text(encoding="utf-8") will raise.
    (reports_dir / "tap-sweep-broken.md").write_bytes(b"\xff\xfe not valid utf-8")

    build_docs(working, site)

    captured = capsys.readouterr()
    assert "WARNING" in captured.out
    assert "tap-sweep-broken.md" in captured.out
    assert (site / "reports" / "tap-project-overview.html").exists()
    assert not (site / "reports" / "tap-sweep-broken.html").exists()
