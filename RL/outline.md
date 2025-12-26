# RL Roadmap (0 → Ready-to-Ship Resume Agent)

This README is a **followable roadmap** that takes you from “I know the basics” to “I can build and explain RL agents end-to-end.”
It’s organized into phases that build on each other, with **learning goals + concrete implementation deliverables**.

---

## Guiding Principle

You’re “RL-ready” when you can do three things without guessing:
1) **Derive** the update rule from first principles (Bellman equations / policy gradients)
2) **Implement** it correctly from scratch (no RL libraries doing the learning for you)
3) **Evaluate + debug** it (learning curves, ablations, seed variance, failure modes)

---

# Phase 0 — First Principles (Tabular RL Mastery)

**Goal:** You can define an MDP, write Bellman equations, explain GPI, and implement the core tabular algorithms: DP, MC, TD, SARSA, Q-learning.

## A) David Silver lectures (Phase 0 subset)
Do these in order:

### Lecture 1 — Introduction to RL
**Learn**
- Returns, rewards, discounting
- Policy vs value function
- Why RL is “trial-and-error + delayed reward”

**You can do**
- Explain what an episode and return are
- Define state, action, reward, transition

### Lecture 2 — MDPs
**Learn**
- Markov property, transition dynamics, reward model
- Value functions: Vπ(s), Qπ(s,a)
- Bellman expectation & optimality equations

**You can do**
- Write Bellman expectation equation for Vπ
- Write Bellman optimality equation for V* or Q*

### Lecture 3 — Planning by Dynamic Programming
**Learn**
- Policy evaluation, policy improvement
- Policy iteration, value iteration
- Generalized policy iteration (GPI)

**You can do**
- Implement tabular policy evaluation
- Implement value iteration for small MDPs

### Lecture 4 — Model-Free Prediction
**Learn**
- Monte Carlo (MC) prediction
- Temporal Difference (TD(0)) prediction
- Bias/variance intuition and bootstrapping

**You can do**
- Explain difference between MC and TD in one paragraph
- Implement MC prediction and TD(0) prediction

### Lecture 5 — Model-Free Control
**Learn**
- MC control (ε-greedy, GLIE ideas)
- SARSA (on-policy), Q-learning (off-policy)
- On-policy vs off-policy, importance sampling intuition

**You can do**
- Implement SARSA and Q-learning tabularly
- Explain why Q-learning is off-policy

---

## B) Sutton & Barto (Phase 0 subset)
Read selectively—these chapters map almost 1:1 to the Silver Phase 0 lectures.

### Chapter 1 — Introduction
**Focus**
- RL framing, agent-environment loop, vocabulary

### Chapter 3 — Finite MDPs
**Focus**
- Formal MDP definition
- Bellman equations (expectation + optimality)

### Chapter 4 — Dynamic Programming
**Focus**
- Policy iteration, value iteration
- How DP backups work and why they converge (intuition)

### Chapter 5 — Monte Carlo Methods
**Focus**
- MC prediction and control
- ε-soft / exploring starts intuition
- Off-policy MC + importance sampling (conceptual)

### Chapter 6 — Temporal-Difference Learning
**Focus**
- TD(0), SARSA, Q-learning
- TD error δ and why bootstrapping matters

### Chapter 12 — Eligibility Traces (only if you’ll do λ / Easy21 Sarsa(λ))
**Focus**
- TD(λ), SARSA(λ)
- Eligibility traces: accumulating/replacing, forward vs backward view (implementation focus)

---

## Phase 0 “Definition of Done”
You can confidently do all of this:

- Define an MDP and compute a return
- Write Bellman expectation and optimality equations
- Explain GPI as “evaluation ↔ improvement”
- Implement (tabular):
  - Policy evaluation
  - Value iteration / policy iteration
  - MC prediction/control
  - TD(0) prediction
  - SARSA
  - Q-learning
- Explain:
  - On-policy vs off-policy
  - Why off-policy often needs correction (importance sampling idea)

---

# Next Step 1 — Project 1: Easy21 (Your “From-Scratch RL” Portfolio Piece)

**Goal:** Turn theory into a complete end-to-end RL implementation with clean plots and a short writeup.

## Deliverables (in order)
### 1) Implement the Easy21 environment
- State, actions, terminal conditions, dealer rules

### 2) Monte Carlo control (tabular)
- ε schedule + α schedule exactly as specified
- Plot V*(s) = max_a Q*(s,a)

### 3) SARSA(λ) (tabular + eligibility traces)
- Sweep λ ∈ {0, 0.1, …, 1}
- Plot MSE vs λ against your MC baseline
- Learning curves for λ=0 and λ=1

### 4) Linear function approximation (coarse coding)
- Implement the 36-feature coarse coding
- Repeat SARSA(λ) experiments under FA
- Discuss: bootstrapping vs MC, stability, approximation tradeoffs

## What this teaches you (why it matters)
- You learn the real mechanics: trajectories, updates, exploration schedules
- You see first-hand how λ changes bias/variance and learning speed
- You bridge directly into “modern RL” (function approximation + stability concerns)

**Make it resume-friendly**
- Include plots in README
- Include a short “Results & Takeaways” section
- Clean code, reproducible seeds, minimal dependencies

---

# Next Step 2 — Project 2: DQN-lite (Neural Value Function Approximation)

**Goal:** Learn how to make value-based deep RL train stably, and learn the engineering discipline (logging, ablations, reproducibility).

## Environment
Start with **CartPole**, then step up to **LunarLander**.

## Build in layers (do not add everything at once)
### Milestone A — Baseline DQN (minimal)
- Q-network
- ε-greedy exploration
- TD loss against a bootstrapped target

### Milestone B — Add replay buffer
- Sample random mini-batches to reduce correlation

### Milestone C — Add target network
- Fixed target network updated periodically to stabilize learning

## Evaluation deliverables
- Learning curves (return vs steps)
- At least **3 random seeds**
- One simple ablation:
  - “without target network” vs “with target network”
  - or “no replay” vs “with replay”

## What to learn conceptually during this step
- Why function approximation + bootstrapping can destabilize learning
- What replay and target networks fix (and what they don’t)
- Reward scaling, learning rates, exploration schedules, gradient stability

---

# Next Step 3 — Project 3: Policy Gradients / Actor-Critic (Stochastic Policies + Continuous Control)

**Goal:** Be able to train agents when value-based methods are awkward (continuous actions, stochastic policies, etc.).

## Part A — REINFORCE with baseline (small discrete task)
- Implement:
  - log π(a|s) gradient update
  - baseline to reduce variance
- Explain in README:
  - why baseline helps (variance reduction)
  - what advantage means (informally)

## Part B — Actor-Critic or PPO/A2C (continuous control)
Use **Pendulum** (continuous actions) as the clean first target.

Minimum deliverables:
- Actor network + critic network (or PPO policy + value)
- Advantage estimate (even a simple one)
- Learning curves, multiple seeds, short ablation (e.g., with/without baseline)

## What to learn conceptually during this step
- Policy gradient theorem (intuition-level is fine)
- Advantage and baselines
- Exploration is “built in” via stochastic policies
- Critic stabilizes/improves the actor update

---

# After Next Step 3 — You’re Ready for the Resume “Full RL Agent” (Capstone)

At this point, you can pick a capstone that looks like real engineering:

## Capstone shape (what makes it impressive)
1) A **custom environment** (or a realistic simulator wrapper)
2) Strong **baselines** (heuristics / PID / threshold policy)
3) A clear **RL algorithm choice** (DQN vs actor-critic)
4) A real evaluation suite:
   - learning curves + seed variance
   - stress tests / distribution shift
   - ablations
5) A polished writeup (“mini-paper” README)

## Two capstone ideas (high value)
- **Call admission / resource allocation** (telecom-style accept/reject decisions)
- **Network send-rate / queue controller** (RL vs PID, maximize throughput while minimizing latency/loss)

---

# Suggested Repository Structure (use this for all projects)

- `env/` (environment + wrappers)
- `agents/` (algorithms)
- `experiments/` (configs, sweep scripts)
- `plots/` (saved figures)
- `results/` (csv/json logs)
- `README.md` (how to run, results, takeaways)
- `requirements.txt` or `environment.yml`

---

# Your Progress Checklist (quick)

## Phase 0 ✅
- [ ] I can derive Bellman equations
- [ ] I can implement MC / TD / SARSA / Q-learning tabularly
- [ ] I can explain on-policy vs off-policy

## Step 1 ✅ Easy21
- [ ] MC control + V*(s) plot
- [ ] SARSA(λ) sweep + MSE plot
- [ ] Linear FA version + discussion

## Step 2 ✅ DQN-lite
- [ ] DQN baseline on CartPole
- [ ] + replay
- [ ] + target net
- [ ] 3 seeds + one ablation

## Step 3 ✅ Policy Gradients
- [ ] REINFORCE + baseline
- [ ] Actor-critic or PPO on Pendulum
- [ ] 3 seeds + one ablation

## Capstone 🎯
- [ ] Custom env + baselines
- [ ] RL agent + evaluation suite
- [ ] Polished writeup + results

---

# Notes (how to avoid common traps)
- Don’t “just run PPO” early—first build the update rules and debug learning.
- Add one stabilization trick at a time (replay, target nets, baselines).
- Always log: returns, episode length, loss terms, exploration parameter, and seed.
- If something fails: reduce complexity (smaller net, easier env, fewer moving parts).

---

If you want, I can also generate:
- a **day-by-day checklist** version of this roadmap, and/or
- a **capstone spec** (environment definition, reward, metrics, baselines, algorithm choice) tailored to the role you’re applying for.

