const test = require("node:test");
const assert = require("node:assert/strict");
const fs = require("node:fs");
const path = require("node:path");

function extractFunction(source, name) {
  const startMarker = `/* ${name}:start */`;
  const endMarker = `/* ${name}:end */`;
  const start = source.indexOf(startMarker);
  const end = source.indexOf(endMarker);
  if (start === -1 || end === -1) {
    throw new Error(`Markers for ${name} not found in index.html`);
  }
  return source.slice(start + startMarker.length, end);
}

const indexHtmlPath = path.join(__dirname, "..", "index.html");
const source = fs.readFileSync(indexHtmlPath, "utf8");
// summaryLineHtml calls highlightMatches (which calls escapeHtml/escapeRegExp)
// to highlight an active search term inside the summary line -- pull all
// three in so the isolated eval below has everything it needs.
const escapeHtmlFunctionSource = extractFunction(source, "escape-html");
const highlightMatchesFunctionSource = extractFunction(source, "highlight-matches");
const functionSource = extractFunction(source, "summary-line");
const combined = escapeHtmlFunctionSource + "\n" + highlightMatchesFunctionSource + "\n" + functionSource;
const summaryLineHtml = (0, eval)(`${combined}\nsummaryLineHtml;`);

test("returns empty string when summary is undefined", () => {
  assert.equal(summaryLineHtml(undefined), "");
});

test("returns empty string when summary is an empty string", () => {
  assert.equal(summaryLineHtml(""), "");
});

test("wraps a present summary in a bold field-summary paragraph", () => {
  assert.equal(
    summaryLineHtml("High confidence on the documented facts."),
    '<p class="field-summary">High confidence on the documented facts.</p>'
  );
});

test("highlights an active search term inside the summary line", () => {
  assert.equal(
    summaryLineHtml("High confidence on the documented facts.", "confidence", false),
    '<p class="field-summary">High <mark class="hl">confidence</mark> on the documented facts.</p>'
  );
});
