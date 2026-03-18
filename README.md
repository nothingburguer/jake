# Jake

**Jake** is a simple, JSON-based build tool inspired by `make`, written in C++. Instead of a `Makefile`, Jake uses a `jakefile.json` to define variables and build targets. The goal is the explicitness and simplicity.

---

> [!WARNING]
> **This repository is an archived mirror — no longer actively maintained here.**
> Development has moved to Codeberg. Issues, pull requests, and contributions
> opened in this repository will not be monitored. For the active repository,
> see the [Codeberg mirror](https://codeberg.org/grassleaff/jake).

---

# Project Migration Notice

This project has been permanently migrated from GitHub to **[Codeberg](https://codeberg.org)**.
The canonical repository is now hosted at:

```
https://codeberg.org/grassleaff/jake
```

This document outlines the technical and ethical rationale behind this decision.

---

## Background

GitHub, acquired by Microsoft in 2018, has undergone a series of policy and structural changes
that progressively conflict with the principles this project upholds: software freedom, user
sovereignty, transparency, and ethical use of contributed code.

The migration to Codeberg is a deliberate response to these changes, not a temporary measure.

---

## Reasons for Migration

### 1. Use of Public Repositories to Train Commercial AI Without Explicit Consent

GitHub Copilot was trained on source code from public repositories, including projects hosted
under licenses that impose specific conditions on use, reproduction, and attribution (e.g., GPL,
LGPL, MPL, AGPL). The GitHub Terms of Service (Section D.8) grant the platform a broad license
to use publicly hosted content for operating and improving its services — which now explicitly
includes AI products.

No effective opt-out mechanism was provided for code already published. Contributors to this
project never consented to having their work used as training data for a commercial product.

This issue resulted in a class-action lawsuit filed in November 2022 against GitHub, Microsoft,
and OpenAI, alleging that Copilot reproduces licensed code without attribution, in violation of
open source license terms.

### 2. Aggressive Platform-Level Integration of Copilot

GitHub has progressively embedded Copilot across its interface — in the code editor, pull request
reviews, issue tracking, and repository suggestions. This makes it functionally difficult to
maintain a project on the platform while enforcing a policy against AI-generated contributions,
as the platform itself actively encourages and normalizes such use.

This concern was explicitly cited by the **Gentoo Linux** project when it announced its migration
to Codeberg, referencing GitHub's "continuous attempts to force Copilot usage" on hosted
repositories.

### 3. Organizational Restructuring: GitHub Absorbed into Microsoft CoreAI

In August 2025, GitHub's CEO Thomas Dohmke departed and the platform was formally integrated into
Microsoft's **CoreAI** division — the same organizational unit responsible for the company's
artificial intelligence strategy. This removed any remaining institutional separation between
GitHub as a developer platform and Microsoft's commercial AI business.

GitHub is no longer an independently operated product. It is a strategic asset in a vertically
integrated AI pipeline.

### 4. Government Contracts Raising Ethical Concerns

Microsoft and GitHub have maintained contracts with agencies such as U.S. Immigration and Customs
Enforcement (ICE), which have drawn sustained criticism from civil liberties organizations and
members of the open source community. Hosting critical project infrastructure on a platform with
these institutional relationships is inconsistent with this project's values.

### 5. DMCA Takedowns and Lack of Due Process

GitHub has a documented history of responding to DMCA takedown requests by removing repositories
with limited notice and inadequate mechanisms for contestation. Notable cases include the removal
of `youtube-dl` in 2020 and various security research repositories.

This represents an operational risk: a project's entire history, issues, and releases can be made
inaccessible without recourse, based on a third-party legal request directed at a centralized
commercial host.

### 6. Geopolitical Access Restrictions

GitHub, as a U.S.-based platform subject to U.S. export controls and sanctions law, has previously
restricted access for developers in sanctioned countries without advance notice. A platform that
can unilaterally revoke access to contributors based on their nationality or location is not
suitable as a long-term home for a project that aims to serve a global community.

---

## Why Codeberg

**[Codeberg](https://codeberg.org)** is operated by **Codeberg e.V.**, a registered non-profit
association based in Berlin, Germany. The platform runs **[Forgejo](https://forgejo.org)**, a
community-governed fork of Gitea, under the terms of the EUPL.

Relevant distinctions:

- Operated as a non-profit with no commercial AI agenda
- No use of hosted repositories for model training
- Subject to EU law, including GDPR, rather than U.S. jurisdiction
- Platform source code is free software and publicly auditable
- Governance is transparent and community-oriented
- Explicitly scoped to free and open source software projects

---

## Contributing

All active development, issue tracking, and pull requests are handled exclusively on Codeberg:

```
https://codeberg.org/grassleaff/jake
```

This GitHub repository is not monitored. Pull requests and issues opened here will be closed
without review.

---

## References

- GitHub Terms of Service, Section D — https://docs.github.com/en/site-policy/github-terms/github-terms-of-service
- *Doe v. GitHub, Inc.* (N.D. Cal., 2022) — class-action complaint regarding Copilot training data
- Gentoo Linux migration announcement — https://www.gentoo.org/news/2024/09/18/codeberg-migration.html
- Forgejo project — https://forgejo.org
- Codeberg e.V. — https://codeberg.org/Codeberg/org/src/branch/main/en/bylaws.md
