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
