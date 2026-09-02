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
// classifyStatus's own outputs are what statusRank() ranks -- pull both in
// together so the "every classifyStatus output is covered by
// STATUS_GROUP_ORDER" test below can call classifyStatus directly rather
// than hardcoding a duplicate list of its labels.
const classifyStatusFunctionSource = extractFunction(source, "classify-status");
const statusRankFunctionSource = extractFunction(source, "status-rank");
const combined = classifyStatusFunctionSource + "\n" + statusRankFunctionSource;
const { classifyStatus, statusRank, STATUS_GROUP_ORDER } = (0, eval)(
  `${combined}\n({ classifyStatus, statusRank, STATUS_GROUP_ORDER });`
);

test("ranks the most procedurally consequential status first", () => {
  assert.equal(statusRank("Impeachment Articles Filed"), 0);
});

test("ranks a resolved/closed status after an active one", () => {
  assert.ok(statusRank("Active Litigation — Pending Ruling") < statusRank("Case Dismissed"));
});

test("ranks an unrecognized category after every named category", () => {
  assert.equal(statusRank("Something New"), STATUS_GROUP_ORDER.length);
});

test("ranks Uncategorized last among named categories", () => {
  const namedRanks = STATUS_GROUP_ORDER.filter(s => s !== "Uncategorized").map(statusRank);
  assert.ok(Math.max(...namedRanks) < statusRank("Uncategorized"));
});

test("every possible classifyStatus() output is covered by STATUS_GROUP_ORDER", () => {
  // Drives classifyStatus with one input string per rule pattern (plus the
  // no-match and empty-input fallbacks) so this test fails loudly if a
  // future classifyStatus edit adds a label that STATUS_GROUP_ORDER forgot
  // to rank -- silently falling to "sorts last" would otherwise be an easy
  // gap to miss.
  const sampleInputs = [
    "impeachment articles were filed",
    "dismissed by a federal judge",
    "a probable cause finding of criminal contempt",
    "the court has ruled against the agency",
    "a GAO finding",
    "an inspector general report",
    "a foia lawsuit is pending",
    "the rule was withdrawn",
    "a congressional investigation is ongoing",
    "a complaint filed with the agency",
    "an ongoing court inquiry",
    "active litigation is ongoing",
    "should be treated as incomplete",
    "no formal action has been taken",
    "some unmatched status text",
    "",
  ];
  sampleInputs.forEach(input => {
    const category = classifyStatus(input);
    assert.ok(
      STATUS_GROUP_ORDER.includes(category),
      `classifyStatus(${JSON.stringify(input)}) returned "${category}", which STATUS_GROUP_ORDER doesn't rank`
    );
  });
});
