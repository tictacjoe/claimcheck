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

// Extract all the functions buildDetailHtml transitively depends on --
// summaryLineHtml for the curated trackers, escapeHtml/highlightMatches
// for the tracker (Reporting) kind's search-term highlighting.
const escapeHtmlFunctionSource = extractFunction(source, "escape-html");
const summaryLineFunctionSource = extractFunction(source, "summary-line");
const highlightMatchesFunctionSource = extractFunction(source, "highlight-matches");
const buildUpdateRequestHtmlFunctionSource = extractFunction(source, "build-update-request-html");
const buildDetailHtmlFunctionSource = extractFunction(source, "build-detail-html");

// Eval them all together so buildDetailHtml can call summaryLineHtml and
// highlightMatches (which itself calls escapeHtml/escapeRegExp), plus
// buildUpdateRequestHtml (which calls escapeHtml directly).
const combined = escapeHtmlFunctionSource + "\n" + summaryLineFunctionSource + "\n" +
  highlightMatchesFunctionSource + "\n" + buildUpdateRequestHtmlFunctionSource + "\n" + buildDetailHtmlFunctionSource;
const buildDetailHtml = (0, eval)(`${combined}\nbuildDetailHtml;`);

test("deregulation with summaries", () => {
  const entry = {
    what_changed: "Agency repealed the rule.",
    estimated_health_impact: {
      summary: "Costs rise."
    },
    confidence_note: "High confidence.",
    section_summaries: {
      what_changed: "Repealed outright.",
      estimated_impact: "Costs rise for workers.",
      confidence_note: "Well-sourced."
    },
    primary_proponent: {
      name: "John Doe",
      role: "Administrator",
      note: ""
    },
    sources: []
  };
  const cfg = { kind: "deregulation" };
  const result = buildDetailHtml(entry, cfg);

  // Check that summary lines are present and come before the paragraph text
  assert(result.includes('<p class="field-summary">Repealed outright.</p>'), "should include what_changed summary");
  assert(result.includes('<p class="field-summary">Costs rise for workers.</p>'), "should include estimated_impact summary");
  assert(result.includes('<p class="field-summary">Well-sourced.</p>'), "should include confidence_note summary");

  // Verify they appear in the right order relative to their content
  const whatChangedIndex = result.indexOf("Repealed outright");
  const whatChangedContentIndex = result.indexOf("Agency repealed the rule");
  assert(whatChangedIndex < whatChangedContentIndex, "what_changed summary should come before content");

  const impactIndex = result.indexOf("Costs rise for workers");
  const impactContentIndex = result.indexOf("Costs rise.");
  assert(impactIndex < impactContentIndex, "estimated_impact summary should come before content");
});

test("deregulation without summaries (regression check)", () => {
  const entry = {
    what_changed: "Agency repealed the rule.",
    estimated_health_impact: {
      summary: "Costs rise."
    },
    confidence_note: "High confidence.",
    // NO section_summaries key at all
    primary_proponent: {
      name: "John Doe",
      role: "Administrator",
      note: ""
    },
    sources: []
  };
  const cfg = { kind: "deregulation" };
  const result = buildDetailHtml(entry, cfg);

  // Should contain ZERO field-summary elements
  assert.equal(
    (result.match(/class="field-summary"/g) || []).length,
    0,
    "should contain zero field-summary classes when no section_summaries"
  );
});

test("govservices with summaries", () => {
  const entry = {
    institution: "Department of Commerce",
    what_changed: "Reduced staffing by 30%.",
    estimated_impact: {
      summary: "Delayed processing times."
    },
    confidence_note: "Moderately confident.",
    section_summaries: {
      what_changed: "Major staffing reduction.",
      estimated_impact: "Processing will slow significantly.",
      confidence_note: "Multiple sources confirm."
    },
    primary_proponent: {
      name: "Jane Smith",
      role: "Secretary",
      note: ""
    },
    sources: []
  };
  const cfg = { kind: "govservices" };
  const result = buildDetailHtml(entry, cfg);

  // Check that summary lines are present
  assert(result.includes('<p class="field-summary">Major staffing reduction.</p>'), "should include what_changed summary");
  assert(result.includes('<p class="field-summary">Processing will slow significantly.</p>'), "should include estimated_impact summary");
  assert(result.includes('<p class="field-summary">Multiple sources confirm.</p>'), "should include confidence_note summary");

  // Verify they appear in the right order relative to their content
  const whatChangedIndex = result.indexOf("Major staffing reduction");
  const whatChangedContentIndex = result.indexOf("Reduced staffing by 30%");
  assert(whatChangedIndex < whatChangedContentIndex, "what_changed summary should come before content");
});

test("govservices (Government Service Redirection) highlights the search term throughout the body", () => {
  const entry = {
    institution: "U.S. Department of Education, Office for Civil Rights",
    what_changed: "Reduced staffing significantly.",
    estimated_impact: {
      summary: "Slower complaint processing.",
      caveat: "Civil rights groups dispute the agency's framing."
    },
    confidence_note: "Civil rights advocates corroborate the timeline.",
    primary_proponent: { name: "Jane Smith", role: "Secretary", note: "" },
    sources: []
  };
  const cfg = { kind: "govservices" };
  const result = buildDetailHtml(entry, cfg, "civil rights", false);

  // institution, caveat, and confidence_note each contain a separate
  // match of the phrase "civil rights" -- all three were previously
  // rendered raw/unhighlighted. Multi-word terms highlight each word
  // independently (matching matchesTerm()'s AND-of-words behavior), so
  // each of the 3 occurrences produces 2 <mark> tags.
  assert.equal(
    (result.match(/<mark class="hl">/g) || []).length,
    6,
    "should highlight the term in institution, caveat, and confidence_note"
  );
});

test("prosecution with summaries", () => {
  const entry = {
    offense_category: "Fraud",
    status_category: "Investigation",
    offense_category_raw: "18 USC § 1001",
    incident_summary: "False statements on federal forms.",
    status: "Under investigation by DOJ.",
    confidence_note: "Strong evidence.",
    section_summaries: {
      incident_summary: "Allegedly submitted fraudulent documents.",
      confidence_note: "Based on witness accounts and documents."
    }
  };
  const cfg = { kind: "prosecution" };
  const result = buildDetailHtml(entry, cfg);

  // Check that summary lines are present
  assert(result.includes('<p class="field-summary">Allegedly submitted fraudulent documents.</p>'), "should include incident_summary summary");
  assert(result.includes('<p class="field-summary">Based on witness accounts and documents.</p>'), "should include confidence_note summary");

  // Verify they appear in the right order relative to their content
  const incidentIndex = result.indexOf("Allegedly submitted fraudulent documents");
  const incidentContentIndex = result.indexOf("False statements on federal forms");
  assert(incidentIndex < incidentContentIndex, "incident_summary summary should come before content");
});

test("prosecution (Cabinet-Level) highlights the search term throughout the body", () => {
  const entry = {
    offense_category: "Civil Rights Violation",
    status_category: "Investigation",
    offense_category_raw: "42 USC 1983",
    incident_summary: "Alleged violation of civil rights during the raid.",
    status: "Under investigation.",
    confidence_note: "Civil rights attorneys corroborate the account.",
    cause: "A civil rights enforcement gap enabled this.",
    rebuttal_anticipated: "Officials may cite civil rights training as a defense.",
    comeback: "That civil rights training claim doesn't survive scrutiny."
  };
  const cfg = { kind: "prosecution" };
  const result = buildDetailHtml(entry, cfg, "civil rights", false);

  // offense_category, incident_summary, confidence_note, cause,
  // rebuttal_anticipated, and comeback each contain a separate match of
  // the phrase "civil rights" -- all six are rendered raw/unhighlighted
  // without this fix (only the card's collapsed meta line was hit for
  // the pre-existing fields; cause/rebuttal_anticipated/comeback weren't
  // rendered at all). Multi-word terms highlight each word independently
  // (matching matchesTerm()'s AND-of-words behavior), so each of the 6
  // occurrences produces 2 <mark> tags.
  assert.equal(
    (result.match(/<mark class="hl">/g) || []).length,
    12,
    "should highlight the term in offense_category, incident_summary, confidence_note, cause, rebuttal_anticipated, and comeback"
  );
});

test("prosecution renders Root Cause, Anticipated Defense, and TAP's Rebuttal after Confidence note", () => {
  const entry = {
    offense_category: "Fraud",
    status_category: "Investigation",
    offense_category_raw: "18 USC § 1001",
    incident_summary: "False statements on federal forms.",
    status: "Under investigation by DOJ.",
    confidence_note: "Strong evidence.",
    cause: "Structural incentive analysis goes here.",
    rebuttal_anticipated: "The likely defense goes here.",
    comeback: "Why that defense doesn't hold up goes here."
  };
  const cfg = { kind: "prosecution" };
  const result = buildDetailHtml(entry, cfg);

  assert(result.includes('<div class="field-label">Root Cause</div><div class="field-value">Structural incentive analysis goes here.</div>'), "should render cause under a Root Cause label");
  assert(result.includes('<div class="field-label">Anticipated Defense</div><div class="field-value">The likely defense goes here.</div>'), "should render rebuttal_anticipated under an Anticipated Defense label");
  assert(result.includes("<div class=\"field-label\">TAP's Rebuttal</div><div class=\"field-value\">Why that defense doesn't hold up goes here.</div>"), "should render comeback under a TAP's Rebuttal label");

  const confidenceIndex = result.indexOf("Confidence note");
  const causeIndex = result.indexOf("Root Cause");
  const rebuttalIndex = result.indexOf("Anticipated Defense");
  const comebackIndex = result.indexOf("TAP's Rebuttal");
  assert(confidenceIndex < causeIndex, "Root Cause should come after Confidence note");
  assert(causeIndex < rebuttalIndex, "Anticipated Defense should come after Root Cause");
  assert(rebuttalIndex < comebackIndex, "TAP's Rebuttal should come after Anticipated Defense");
});

test("tracker (Reporting) highlights the search term in the body", () => {
  const entry = {
    what_happened: "The EPA announced new rules today.",
    source_name: "Example Substack",
    source_url: "https://example.com/post",
  };
  const cfg = { kind: "tracker" };
  const result = buildDetailHtml(entry, cfg, "EPA", false);

  assert(
    result.includes('<mark class="hl">EPA</mark>'),
    "should wrap the matched term in the body text with a <mark> highlight"
  );
});

test("tracker (Reporting) highlights the search term inside the source name", () => {
  const entry = {
    what_happened: "Some unrelated announcement.",
    source_name: "Civil Rights Group Sues Over New Policy",
    source_url: "https://example.com/post",
  };
  const cfg = { kind: "tracker" };
  const result = buildDetailHtml(entry, cfg, "civil rights", false);

  assert(
    result.includes('<mark class="hl">Civil Rights</mark>'),
    "should wrap the matched term in the source name with a <mark> highlight"
  );
});

test("tracker (Reporting) with no active search term leaves body unhighlighted but escaped", () => {
  const entry = {
    what_happened: "Rules & <regulations> changed.",
    source_name: "",
  };
  const cfg = { kind: "tracker" };
  const result = buildDetailHtml(entry, cfg, "", false);

  assert(!result.includes('<mark class="hl">'), "should not highlight anything when no term is active");
  assert(result.includes("Rules &amp; &lt;regulations&gt; changed."), "should still HTML-escape the raw body text");
});

test("deregulation shows last verified date and a request-update button", () => {
  const entry = {
    id: "some-rule-id",
    rule_name: "Some Rule",
    last_verified: "2026-08-01",
    primary_proponent: {},
    estimated_health_impact: {},
  };
  const cfg = { kind: "deregulation", idField: "id", titleField: "rule_name" };
  const result = buildDetailHtml(entry, cfg);

  assert(result.includes('<span class="field-value">Last verified 2026-08-01</span>'), "should show the last_verified date");
  assert(result.includes('class="suggest-submit-btn request-update-btn"'), "should include the request-update button");
  assert(result.includes('data-tracker="deregulation"'), "button should carry the tracker key");
  assert(result.includes('data-entry-id="some-rule-id"'), "button should carry the entry id");
  assert(result.includes('data-entry-title="Some Rule"'), "button should carry the entry title");
});

test("prosecution falls back to a placeholder when last_verified is missing", () => {
  const entry = {
    id: "some-official-id",
    official: "Some Official, Some Title",
    offense_category: "Fraud",
    status_category: "Investigation",
    incident_summary: "Summary.",
    status: "Under investigation.",
    confidence_note: "Strong evidence.",
  };
  const cfg = { kind: "prosecution", idField: "id", titleField: "official" };
  const result = buildDetailHtml(entry, cfg);

  assert(result.includes('<span class="field-value">Last verified not yet recorded</span>'), "should show the fallback text when last_verified is absent");
});

test("govservices request-update button carries the correct tracker and entry id", () => {
  const entry = {
    id: "some-action-id",
    title: "Some Action",
    institution: "Some Agency",
    last_verified: "2026-07-15",
    estimated_impact: {},
  };
  const cfg = { kind: "govservices", idField: "id", titleField: "title" };
  const result = buildDetailHtml(entry, cfg);

  assert(result.includes('<span class="field-value">Last verified 2026-07-15</span>'), "should show the last_verified date");
  assert(result.includes('data-tracker="govservices"'), "button should carry the govservices tracker key");
  assert(result.includes('data-entry-id="some-action-id"'), "button should carry the entry id");
});
