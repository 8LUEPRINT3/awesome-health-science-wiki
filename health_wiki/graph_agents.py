import sys
import os
from knowledge_graph import add_entity, add_relation, init_db

class AgentCoordinator:
    def __init__(self):
        print("[System] Initializing Graph-Grounded Multi-Agent Pipeline...")
        init_db()

    def architect_phase(self, objective):
        print(f"\n[Architect Agent] Planning and reflecting on objective: '{objective}'")
        plan_id = "plan_v1"
        add_entity(plan_id, "Artifact", "Execution Plan", {"objective": objective})
        return {"plan_id": plan_id, "steps": ["Step 1: Setup structure", "Step 2: Implement code", "Step 3: Review"]}

    def tech_lead_phase(self, plan):
        print(f"\n[Tech Lead Agent] Reviewing plan and routing tasks...")
        review_id = "review_v1"
        add_entity(review_id, "Artifact", "Tech Review", {"status": "approved"})
        add_relation(review_id, plan['plan_id'], "validates", "Tech Lead Review")
        return True

    def developer_phase(self):
        print(f"\n[Developer Agent] Executing code implementation and writing to workspace...")
        dev_artifact = "code_impl_v1"
        add_entity(dev_artifact, "Artifact", "Source Code", {"status": "completed"})
        return dev_artifact

    def run(self, objective):
        plan = self.architect_phase(objective)
        if self.tech_lead_phase(plan):
            artifact = self.developer_phase()
            print(f"\n[Pipeline Complete] Successfully generated artifact: {artifact} linked in Knowledge Graph.")

if __name__ == "__main__":
    coordinator = AgentCoordinator()
    coordinator.run("Build Health Science Wiki Integration Module")
