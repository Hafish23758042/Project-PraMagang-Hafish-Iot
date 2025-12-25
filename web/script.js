const app = Vue.createApp({
    data() {
        return { logs: [], prediction: "", chart: null }
    },
    methods: {
        async updateData() {
            try {
                const res = await fetch(`http://localhost:5000/api/data?t=${new Date().getTime()}`);
                const data = await res.json();
                this.logs = data.logs || [];
                this.renderChart();
            } catch (e) { console.error("Koneksi Flask mati"); }
        },
        renderChart() {
            const canvas = document.getElementById('myChart');
            if (!canvas || this.logs.length === 0) return;
            const ctx = canvas.getContext('2d');
            if (this.chart) this.chart.destroy();
            const d = [...this.logs].reverse();
            this.chart = new Chart(ctx, {
                type: 'line',
                data: {
                    labels: d.map(l => l.time),
                    datasets: [{
                        label: 'Level Air (cm)',
                        data: d.map(l => l.level),
                        borderColor: '#00d4ff',
                        backgroundColor: 'rgba(0, 212, 255, 0.1)',
                        fill: true, tension: 0.4
                    }]
                },
                options: { responsive: true, maintainAspectRatio: false, animation: false }
            });
        },
        async sendCmd(cmd) {
            await fetch('http://localhost:5000/api/control', {
                method: 'POST',
                headers: { 'Content-Type': 'application/json' },
                body: JSON.stringify({ command: cmd })
            });
            alert("Perintah Manual " + cmd + " Terkirim! (Berlaku 10 detik)");
        }
    },
    mounted() {
        this.updateData();
        setInterval(this.updateData, 3000);
    }
}).mount('#app');