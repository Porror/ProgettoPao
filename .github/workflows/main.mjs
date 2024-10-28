import { Octokit } from "@octokit/core";
import fetch from "node-fetch";  // Import node-fetch

const octokit = new Octokit({ 
  auth: process.env.GITHUB_TOKEN,
  request: { fetch }  // Set fetch implementation
});

async function closeCompletedIssues() {
  const [owner, repo] = process.env.GITHUB_REPOSITORY.split('/');
  const { data: issues } = await octokit.request('GET /repos/{owner}/{repo}/issues', {
    owner,
    repo,
    state: 'open'
  });

  for (const issue of issues) {
    const body = issue.body || "";
    const tasks = body.match(/- \[([ xX])\]/g) || [];
    const allTasksCompleted = tasks.length > 0 && tasks.every(task => task.includes('[x]') || task.includes('[X]'));

    if (allTasksCompleted) {
      await octokit.request('PATCH /repos/{owner}/{repo}/issues/{issue_number}', {
        owner,
        repo,
        issue_number: issue.number,
        state: 'closed'
      });
      console.log(`Closed issue #${issue.number} - "${issue.title}"`);
    }
  }
}

closeCompletedIssues().catch(error => console.error(error));
