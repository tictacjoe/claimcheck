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

// Extract both functions -- summaryLineHtml first, then buildDetailHtml
const summaryLineFunctionSource = extractFunction(source, "summary-line");
const buildDetailHtmlFunctionSource = extractFunction(source, "build-detail-html");

// Eval both together so buildDetailHtml can call summaryLineHtml
const combined = summaryLineFunctionSource + "\n" + buildDetailHtmlFunctionSource;
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
