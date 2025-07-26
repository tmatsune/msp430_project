
# 1. Create a new feature branch from current branch (usually main)
git checkout -b feature/your-feature-name
# 2. Stage and commit changes
git add .
git commit -m "Describe what you did"
# 3. Push to GitHub and track upstream branch
git push -u origin feature/your-feature-name

--- 

👉 Then on GitHub:
Open a Pull Request (PR) into main or dev
Wait for CI checks (if any)
Get review/approval
Merge the PR

--- 

# 4. Fetch all updates from GitHub
git fetch origin
# 5. Switch to main
git checkout main
# 6. Pull latest changes (merged PR)
git pull origin main
# 7. (Optional) Delete the feature branch locally
git branch -d feature/your-feature-name
# 8. (Optional) Delete the feature branch from remote
git push origin --delete feature/your-feature-name


